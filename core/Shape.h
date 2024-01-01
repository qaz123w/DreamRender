#pragma once

#include "Utils.h"
#include "Transform.h"
#include "Material.h"

enum ShapeType {
	TriangleMeshShape,
	SphereShape,
	QuadShape,
};

class Shape {
	friend Light;

public:
	Shape(ShapeType type, std::shared_ptr<Material> m, const Transform& trans, int geom_id = 0) :
	    m_type(type), material(m), transform(trans), geometry_id(geom_id) {}

	inline ShapeType GetType() const {
		return m_type;
	}

	inline virtual Vector3f GetGeometryNormal(uint32_t faceID, const Point2f& barycentric) const {
		return Point3f(0.0f);
	}

	inline virtual Vector3f GetShadeNormal(uint32_t faceID, const Point2f& barycentric) const { 
		return Vector3f(0.0f); 
	}

	inline virtual Point2f GetTexcoords(uint32_t faceID, const Point2f& barycentric) const { 
		return Point2f(0.0f); 
	}

	// Creating and committing the current object to Embree scene
	virtual int ConstructEmbreeObject(RTCDevice& rtc_device, RTCScene& rtc_scene) = 0;

protected:
	// Position before any transformation
	ShapeType m_type;
	Transform transform;
	int geometry_id;
	std::shared_ptr<Material> material;
};

class TriangleMesh : public Shape {
public:
	TriangleMesh(std::shared_ptr<Material> m, const std::string& file, const Transform& trans);

	inline uint32_t Vertices() const { 
		return vertices.size() / 3; 
	}

	inline uint32_t Faces() const { 
		return indices.size() / 3; 
	}

	struct VertexIndices {
	    uint32_t v1idx;
	    uint32_t v2idx;
	    uint32_t v3idx;
    };

	inline VertexIndices GetIndices(uint32_t faceID) const {
		VertexIndices ret;
		ret.v1idx = indices[3 * faceID + 0];
		ret.v2idx = indices[3 * faceID + 1];
		ret.v3idx = indices[3 * faceID + 2];

		return ret;
	}

	// return vertex
	inline Vector3f GetVertex(uint32_t vertexID) const {
		return Vector3f(vertices[3 * vertexID + 0], vertices[3 * vertexID + 1],
			vertices[3 * vertexID + 2]);
	}

	// return vertex normal
	inline Vector3f GetVertexNormal(uint32_t vertexID) const {
		return Vector3f(normals[3 * vertexID + 0], normals[3 * vertexID + 1],
			normals[3 * vertexID + 2]);
	}

	// return vertex texcoords
	inline Point2f GetVertexTexcoords(uint32_t vertexID) const {
		return Point2f(texcoords[2 * vertexID + 0], texcoords[2 * vertexID + 1]);
	}

	// compute position of specified face, barycentric
	inline virtual Vector3f GetGeometryNormal(uint32_t faceID, const Point2f& barycentric) const {
		const VertexIndices vidx = GetIndices(faceID);
		const Point3f A = GetVertex(vidx.v1idx);
		const Point3f B = GetVertex(vidx.v2idx);
		const Point3f C = GetVertex(vidx.v3idx);

		return glm::normalize(glm::cross(B - A, C - A));
	}

	// compute normal of specified face, barycentric
	inline Vector3f GetShadeNormal(uint32_t faceID, const Point2f& barycentric) const override {
		const VertexIndices vidx = GetIndices(faceID);
		const Vector3f n1 = GetVertexNormal(vidx.v1idx);
		const Vector3f n2 = GetVertexNormal(vidx.v2idx);
		const Vector3f n3 = GetVertexNormal(vidx.v3idx);

		return glm::normalize(n1 * (1.0f - barycentric[0] - barycentric[1]) + n2 * barycentric[0] +
			n3 * barycentric[1]);
	}

	// compute texcoords of specified face, barycentric
	inline Point2f GetTexcoords(uint32_t faceID, const Point2f& barycentric) const override {
		const VertexIndices vidx = GetIndices(faceID);
		const Point2f t1 = GetVertexTexcoords(vidx.v1idx);
		const Point2f t2 = GetVertexTexcoords(vidx.v2idx);
		const Point2f t3 = GetVertexTexcoords(vidx.v3idx);

		return t1 * (1.0f - barycentric[0] - barycentric[1]) + t2 * barycentric[0] +
			t3 * barycentric[1];
	}

	// Creating and commiting the current object to Embree scene
	virtual int ConstructEmbreeObject(RTCDevice& rtc_device, RTCScene& rtc_scene) override;

private:
	std::vector<float> vertices;
	std::vector<uint32_t> indices;
	std::vector<float> normals;
	std::vector<float> texcoords;
};

class Sphere : public Shape {
public:
	Sphere(std::shared_ptr<Material> m, Point3f cen, float rad) : Shape(ShapeType::SphereShape, m, Transform()), center(cen), radius(rad) {}

	// User defined intersection functions for the Sphere primitive
	static void SphereBoundsFunc(const struct RTCBoundsFunctionArguments* args);

	static void SphereIntersectFunc(const RTCIntersectFunctionNArguments* args);

	static void SphereOccludedFunc(const RTCOccludedFunctionNArguments* args);

	// Creating and commiting the current object to Embree scene
	virtual int ConstructEmbreeObject(RTCDevice& rtc_device, RTCScene& rtc_scene) override;

	static Point2f GetSphereUV(const Point3f& surface_pos, const Point3f& center);

private:
	Point3f center;
	float radius;
};

class Quad : public Shape {
	friend QuadArea;

public:
	Quad(std::shared_ptr<Material> m, const Point3f& pos, const Vector3f& _u, const Vector3f& _v) : Shape(ShapeType::QuadShape, m, Transform()), position(pos), u(_u), v(_v) {}

	// Creating and commiting the current object to Embree scene
	virtual int ConstructEmbreeObject(RTCDevice& rtc_device, RTCScene& rtc_scene) override;

	static Point2f GetQuadUV(const Point3f& p, const Point3f& position, const Vector3f& u, const Vector3f& v);

private:
	Point3f position;
	Vector3f u;
	Vector3f v;
};