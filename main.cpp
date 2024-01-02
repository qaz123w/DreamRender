#include "Renderer.h"

int main() {
	int Width = 800;
	int Height = 800;

	Transform tran;
	Pinhole camera(Point3f(10.0f), Point3f(0.0f), Vector3f(0.0f, 1.0f, 0.0f), 1.0f, 60.0f, (float)Width / (float)Height);
	//Thinlens camera2(Point3f(10.0f, 8.0f, 10.0f), Point3f(0.0f), Vector3f(0.0f, 1.0f, 0.0f), 1.0f, 60.0f, (float)Width / (float)Height, 2.0f);
	PostProcessing post(std::make_shared<ACES>());
	RTCDevice rtc_device = rtcNewDevice(NULL);
	Scene scene(rtc_device);

	float albedo[3] = { 0.9f, 0.9f, 0.9f };
	float roughness[3] = { 0.1f, 0.1f, 0.1f };
	auto material = std::make_shared<Diffuse>(std::make_shared<Constant>(RGBSpectrum::FromRGB(albedo)), std::make_shared<Constant>(RGBSpectrum::FromRGB(roughness)));

	//scene.AddShape(new Sphere(material, Point3f(0.0f, 0.0f, 0.0f), 3.0f));
	scene.AddShape(new TriangleMesh(material, "teapot.obj", tran));
	scene.SetCamera(std::make_shared<Pinhole>(camera));
	scene.Commit();

	VolumetricPathTracing vpt(std::make_shared<Scene>(scene), std::make_shared<Independent>(), std::make_shared<Gaussian>(), Width, Height, 5);
	Renderer renderer(std::make_shared<VolumetricPathTracing>(vpt), post);

	renderer.Run();

	return 0;
}
