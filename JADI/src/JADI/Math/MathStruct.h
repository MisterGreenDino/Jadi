#pragma once

struct Vec3 { float x, y, z; };
struct Vec4 { float x, y, z, w; };
struct Matrix { float data[4][4]; };

struct Vertex { Vec3 position; Vec3 color; };
struct Mesh { int v0_id, v1_id, v2_id; };
