#include "default_editor/Editor_Axis.h"

#include "math/Constant.h"

#include "render/render_system/Render_Data_Struct.h"

namespace NameSpace_Editor {

	using NameSpace_Core::NameSpace_Math::Math_PI;

	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Buffer_Data;
	using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Mesh_Vertex_Data_Definition;
	//using NameSpace_Function::NameSpace_Render::NameSpace_Render_System::Mesh_Vertx_Binding_Data_Definition;

	Editor_Translation_Axis::Editor_Translation_Axis(void) {
		// create translation axis render mesh

		const float radius = 0.031f;
		const int   segments = 12;

		uint32_t stride = sizeof(Mesh_Vertex_Data_Definition);

		// vertex
		size_t vertex_data_size = static_cast<unsigned long long>((3 * segments + 2)) * 3 * static_cast<size_t>(stride);
		this->Mesh_Data.Static_Mesh_Data.Vertex_Buffer = std::make_shared<Buffer_Data>(vertex_data_size);
		uint8_t* vertex_data = static_cast<uint8_t*>(this->Mesh_Data.Static_Mesh_Data.Vertex_Buffer->Data);

		// x
		for (int i = 0; i < segments; ++i)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride);
			vertex.X = 0.0f;
			vertex.Y = sin(i * 2 * Math_PI / segments) * radius;
			vertex.Z = cos(i * 2 * Math_PI / segments) * radius;
			vertex.U = 0.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}

		for (int i = 0; i < segments; ++i)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (1 * segments + i) * stride);
			vertex.X = 1.5f;
			vertex.Y =
				(*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride)).Y;
			vertex.Z =
				(*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride)).Z;
			vertex.U = 0.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}

		for (int i = 0; i < segments; ++i)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + i) * stride);
			vertex.X = 1.5f;
			vertex.Y =
				(*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride)).Y *
				4.5f;
			vertex.Z =
				(*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride)).Z *
				4.5f;
			vertex.U = 0.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		{
			Mesh_Vertex_Data_Definition& vertex_0 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (3 * segments + 0) * stride);
			vertex_0.X = 1.5f;
			vertex_0.Y = 0.0f;
			vertex_0.Z = 0.0f;
			vertex_0.U = 0.0f;

			vertex_0.NX = vertex_0.NY = vertex_0.NZ = 0.0f;
			vertex_0.TX = vertex_0.TY = vertex_0.TZ = 0.0f;
			vertex_0.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex_1 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (3 * segments + 1) * stride);
			vertex_1.X = 1.9f;
			vertex_1.Y = 0.0f;
			vertex_1.Z = 0.0f;
			vertex_1.U = 0.0f;

			vertex_1.NX = vertex_1.NY = vertex_1.NZ = 0.0f;
			vertex_1.TX = vertex_1.TY = vertex_1.TZ = 0.0f;
			vertex_1.V = 0.0f;
		}

		// y, z
		for (int i = 0; i < 3 * segments + 2; ++i)
		{
			Mesh_Vertex_Data_Definition& vertex_y =
				*(Mesh_Vertex_Data_Definition*)(vertex_data +
					((3 * segments + 2) * 1 + i) * stride);
			vertex_y.X = -(*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Y;
			vertex_y.Y = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).X;
			vertex_y.Z = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Z;
			vertex_y.U = 1.0f;

			vertex_y.NX = vertex_y.NY = vertex_y.NZ = 0.0f;
			vertex_y.TX = vertex_y.TY = vertex_y.TZ = 0.0f;
			vertex_y.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex_z =
				*(Mesh_Vertex_Data_Definition*)(vertex_data +
					((3 * segments + 2) * 2 + i) * stride);
			vertex_z.X = -(*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Z;
			vertex_z.Y = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Y;
			vertex_z.Z = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).X;
			vertex_z.U = 2.0f;

			vertex_z.NX = vertex_z.NY = vertex_z.NZ = 0.0f;
			vertex_z.TX = vertex_z.TY = vertex_z.TZ = 0.0f;
			vertex_z.V = 0.0f;
		}

		size_t index_data_size = (4 * segments * 3) * 3 * sizeof(uint16_t);
		this->Mesh_Data.Static_Mesh_Data.Index_Buffer = std::make_shared<Buffer_Data>(index_data_size);
		uint16_t* index_data = static_cast<uint16_t*>(this->Mesh_Data.Static_Mesh_Data.Index_Buffer->Data);

		for (int i = 0; i < segments; ++i)
		{
			index_data[0 * segments * 3 + i * 6 + 0] = (uint16_t)(0 * segments + i);
			index_data[0 * segments * 3 + i * 6 + 1] = (uint16_t)1 * segments + i;
			index_data[0 * segments * 3 + i * 6 + 2] = (uint16_t)1 * segments + ((i + 1) % segments);

			index_data[0 * segments * 3 + i * 6 + 3] = (uint16_t)1 * segments + ((i + 1) % segments);
			index_data[0 * segments * 3 + i * 6 + 4] = (uint16_t)0 * segments + ((i + 1) % segments);
			index_data[0 * segments * 3 + i * 6 + 5] = (uint16_t)0 * segments + i;
		}
		for (int i = 0; i < segments; ++i)
		{
			index_data[2 * segments * 3 + i * 3 + 0] = (uint16_t)3 * segments + 0;
			index_data[2 * segments * 3 + i * 3 + 1] = (uint16_t)2 * segments + i;
			index_data[2 * segments * 3 + i * 3 + 2] = (uint16_t)2 * segments + ((i + 1) % segments);
		}
		for (int i = 0; i < segments; ++i)
		{
			index_data[3 * segments * 3 + i * 3 + 0] = (uint16_t)2 * segments + i;
			index_data[3 * segments * 3 + i * 3 + 1] = (uint16_t)3 * segments + 1;
			index_data[3 * segments * 3 + i * 3 + 2] = (uint16_t)2 * segments + ((i + 1) % segments);
		}

		for (int i = 0; i < 4 * segments * 3; ++i)
		{
			index_data[4 * segments * 3 * 1 + i] = (uint16_t)((3 * segments + 2) * 1) + index_data[i];
			index_data[4 * segments * 3 * 2 + i] = (uint16_t)((3 * segments + 2) * 2) + index_data[i];
		}
	}

	Editor_Rotation_Axis::Editor_Rotation_Axis()
	{
		// create rotation axis render mesh

		const float inner_radius = 0.9f;
		const float outer_radius = 1.0f;
		const int   segments = 24;

		uint32_t stride = sizeof(Mesh_Vertex_Data_Definition);

		// vertex
		size_t vertex_data_size = static_cast<unsigned long long>(2 * 3) * segments * static_cast<size_t>(stride);
		this->Mesh_Data.Static_Mesh_Data.Vertex_Buffer = std::make_shared<Buffer_Data>(vertex_data_size);
		uint8_t* vertex_data = static_cast<uint8_t*>(this->Mesh_Data.Static_Mesh_Data.Vertex_Buffer->Data);

		// inner xy
		for (int i = 0; i < segments; i++)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride);
			vertex.X = cos(2 * Math_PI / segments * i) * inner_radius;
			vertex.Y = sin(2 * Math_PI / segments * i) * inner_radius;
			vertex.Z = 0.0f;
			vertex.U = 2.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		// outer xy
		for (int i = 0; i < segments; i++)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (1 * segments + i) * stride);
			vertex.X = cos(2 * Math_PI / segments * i) * outer_radius;
			vertex.Y = sin(2 * Math_PI / segments * i) * outer_radius;
			vertex.Z = 0.0f;
			vertex.U = 2.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		// inner yz
		for (int i = 0; i < segments; i++)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + i) * stride);
			vertex.X = 0.0f;
			vertex.Y = cos(2 * Math_PI / segments * i) * inner_radius;
			vertex.Z = sin(2 * Math_PI / segments * i) * inner_radius;
			vertex.U = 0.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		// outer yz
		for (int i = 0; i < segments; i++)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (3 * segments + i) * stride);
			vertex.X = 0.0f;
			vertex.Y = cos(2 * Math_PI / segments * i) * outer_radius;
			vertex.Z = sin(2 * Math_PI / segments * i) * outer_radius;
			vertex.U = 0.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		// inner xz
		for (int i = 0; i < segments; i++)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (4 * segments + i) * stride);
			vertex.X = cos(2 * Math_PI / segments * i) * inner_radius;
			vertex.Y = 0.0f;
			vertex.Z = sin(2 * Math_PI / segments * i) * inner_radius;
			vertex.U = 1.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		// outer xz
		for (int i = 0; i < segments; i++)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (5 * segments + i) * stride);
			vertex.X = cos(2 * Math_PI / segments * i) * outer_radius;
			vertex.Y = 0.0f;
			vertex.Z = sin(2 * Math_PI / segments * i) * outer_radius;
			vertex.U = 1.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}

		// index
		size_t index_data_size = 2 * 3 * segments * 3 * sizeof(uint16_t);
		this->Mesh_Data.Static_Mesh_Data.Index_Buffer = std::make_shared<Buffer_Data>(index_data_size);
		uint16_t* index_data = static_cast<uint16_t*>(this->Mesh_Data.Static_Mesh_Data.Index_Buffer->Data);

		// xoy inner
		for (int i = 0; i < segments; i++)
		{
			index_data[(3 * i) + 0] = (uint16_t)(i % segments);
			index_data[(3 * i) + 1] = (uint16_t)((i + 1) % segments);
			index_data[(3 * i) + 2] = (uint16_t)(i % segments + segments);
		}
		// xoy outer
		for (int i = 0; i < segments; i++)
		{
			index_data[1 * 3 * segments + (3 * i) + 0] = (uint16_t)(i % segments + segments);
			index_data[1 * 3 * segments + (3 * i) + 1] = (uint16_t)((i + 1) % segments + segments);
			index_data[1 * 3 * segments + (3 * i) + 2] = (uint16_t)((i + 1) % segments);
		}
		// yoz inner
		for (int i = 0; i < segments; i++)
		{
			index_data[2 * 3 * segments + (3 * i) + 0] = (uint16_t)(i % segments + segments * 2);
			index_data[2 * 3 * segments + (3 * i) + 1] = (uint16_t)((i + 1) % segments + segments * 2);
			index_data[2 * 3 * segments + (3 * i) + 2] = (uint16_t)(i % segments + segments * 3);
		}
		// yoz outer
		for (int i = 0; i < segments; i++)
		{
			index_data[3 * 3 * segments + (3 * i) + 0] = (uint16_t)(i % segments + segments * 3);
			index_data[3 * 3 * segments + (3 * i) + 1] = (uint16_t)((i + 1) % segments + segments * 3);
			index_data[3 * 3 * segments + (3 * i) + 2] = (uint16_t)((i + 1) % segments + segments * 2);
		}
		// xoz inner
		for (int i = 0; i < segments; i++)
		{
			index_data[4 * 3 * segments + (3 * i) + 0] = (uint16_t)(i % segments + segments * 4);
			index_data[4 * 3 * segments + (3 * i) + 1] = (uint16_t)((i + 1) % segments + segments * 4);
			index_data[4 * 3 * segments + (3 * i) + 2] = (uint16_t)(i % segments + segments * 5);
		}
		// xoz outer
		for (int i = 0; i < segments; i++)
		{
			index_data[5 * 3 * segments + (3 * i) + 0] = (uint16_t)(i % segments + segments * 5);
			index_data[5 * 3 * segments + (3 * i) + 1] = (uint16_t)((i + 1) % segments + segments * 5);
			index_data[5 * 3 * segments + (3 * i) + 2] = (uint16_t)((i + 1) % segments + segments * 4);
		}
	}

	Editor_Scale_Axis::Editor_Scale_Axis() {
		const float radius = 0.031f;
		const int   segments = 12;

		uint32_t stride = sizeof(Mesh_Vertex_Data_Definition);

		// vertex
		size_t vertex_data_size = ((2 * segments + 8) * 3 + 8) * stride;
		this->Mesh_Data.Static_Mesh_Data.Vertex_Buffer = std::make_shared<Buffer_Data>(vertex_data_size);
		uint8_t* vertex_data = static_cast<uint8_t*>(this->Mesh_Data.Static_Mesh_Data.Vertex_Buffer->Data);

		for (int i = 0; i < segments; ++i)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride);
			vertex.X = 0.0f;
			vertex.Y = sin(i * 2 * Math_PI / segments) * radius;
			vertex.Z = cos(i * 2 * Math_PI / segments) * radius;
			vertex.U = 0.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		for (int i = 0; i < segments; ++i)
		{
			Mesh_Vertex_Data_Definition& vertex =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (1 * segments + i) * stride);
			vertex.X = 1.6 - radius * 10;
			vertex.Y = (*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride)).Y;
			vertex.Z = (*(Mesh_Vertex_Data_Definition*)(vertex_data + (0 * segments + i) * stride)).Z;
			vertex.U = 0.0f;

			vertex.NX = vertex.NY = vertex.NZ = 0.0f;
			vertex.TX = vertex.TY = vertex.TZ = 0.0f;
			vertex.V = 0.0f;
		}
		{
			Mesh_Vertex_Data_Definition& vertex0 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 0) * stride);
			vertex0.X = 1.6 - radius * 10;
			vertex0.Y = +radius * 5;
			vertex0.Z = +radius * 5;
			vertex0.U = 0.0f;

			vertex0.NX = vertex0.NY = vertex0.NZ = 0.0f;
			vertex0.TX = vertex0.TY = vertex0.TZ = 0.0f;
			vertex0.TY = 0.0f;

			Mesh_Vertex_Data_Definition& vertex1 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 1) * stride);
			vertex1.X = 1.6 - radius * 10;
			vertex1.Y = +radius * 5;
			vertex1.Z = -radius * 5;
			vertex1.U = 0.0f;

			vertex1.NX = vertex1.NY = vertex1.NZ = 0.0f;
			vertex1.TX = vertex1.TY = vertex1.TZ = 0.0f;
			vertex1.TY = 0.0f;

			Mesh_Vertex_Data_Definition& vertex2 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 2) * stride);
			vertex2.X = 1.6 - radius * 10;
			vertex2.Y = -radius * 5;
			vertex2.Z = +radius * 5;
			vertex2.U = 0.0f;

			vertex2.NX = vertex2.NY = vertex2.NZ = 0.0f;
			vertex2.TX = vertex2.TY = vertex2.TZ = 0.0f;
			vertex2.TY = 0.0f;

			Mesh_Vertex_Data_Definition& vertex3 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 3) * stride);
			vertex3.X = 1.6 - radius * 10;
			vertex3.Y = -radius * 5;
			vertex3.Z = -radius * 5;
			vertex3.U = 0.0f;

			vertex3.NX = vertex3.NY = vertex3.NZ = 0.0f;
			vertex3.TX = vertex3.TY = vertex3.TZ = 0.0f;
			vertex3.TY = 0.0f;

			Mesh_Vertex_Data_Definition& vertex4 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 4) * stride);
			vertex4.X = 1.6;
			vertex4.Y = +radius * 5;
			vertex4.Z = +radius * 5;
			vertex4.U = 0.0f;

			vertex4.NX = vertex4.NY = vertex4.NZ = 0.0f;
			vertex4.TX = vertex4.TY = vertex4.TZ = 0.0f;
			vertex4.TY = 0.0f;

			Mesh_Vertex_Data_Definition& vertex5 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 5) * stride);
			vertex5.X = 1.6;
			vertex5.Y = +radius * 5;
			vertex5.Z = -radius * 5;
			vertex5.U = 0.0f;

			vertex5.NX = vertex5.NY = vertex5.NZ = 0.0f;
			vertex5.TX = vertex5.TY = vertex5.TZ = 0.0f;
			vertex5.TY = 0.0f;

			Mesh_Vertex_Data_Definition& vertex6 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 6) * stride);
			vertex6.X = 1.6;
			vertex6.Y = -radius * 5;
			vertex6.Z = +radius * 5;
			vertex6.U = 0.0f;

			vertex6.NX = vertex6.NY = vertex6.NZ = 0.0f;
			vertex6.TX = vertex6.TY = vertex6.TZ = 0.0f;
			vertex6.TY = 0.0f;

			Mesh_Vertex_Data_Definition& vertex7 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (2 * segments + 7) * stride);
			vertex7.X = 1.6;
			vertex7.Y = -radius * 5;
			vertex7.Z = -radius * 5;
			vertex7.U = 0.0f;

			vertex7.NX = vertex7.NY = vertex7.NZ = 0.0f;
			vertex7.TX = vertex7.TY = vertex7.TZ = 0.0f;
			vertex7.TY = 0.0f;
		}

		for (int i = 0; i < 2 * segments + 8; ++i)
		{
			Mesh_Vertex_Data_Definition& vertex1 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + ((2 * segments + 8) * 1 + i) * stride);
			vertex1.X = -(*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Y;
			vertex1.Y = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).X;
			vertex1.Z = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Z;
			vertex1.U = 1.0f;

			vertex1.NX = vertex1.NY = vertex1.NZ = 0.0f;
			vertex1.TX = vertex1.TY = vertex1.TZ = 0.0f;
			vertex1.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex2 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + ((2 * segments + 8) * 2 + i) * stride);
			vertex2.X = -(*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Z;
			vertex2.Y = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).Y;
			vertex2.Z = (*(Mesh_Vertex_Data_Definition*)(vertex_data + i * stride)).X;
			vertex2.U = 2.0f;

			vertex2.NX = vertex2.NY = vertex2.NZ = 0.0f;
			vertex2.TX = vertex2.TY = vertex2.TZ = 0.0f;
			vertex2.V = 0.0f;
		}

		int start_vertex_index = (2 * segments + 8) * 3;
		{
			Mesh_Vertex_Data_Definition& vertex0 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 0) * stride);
			vertex0.X = 0.0f;
			vertex0.Y = 0.0f;
			vertex0.Z = 0.0f;
			vertex0.U = 6.0f;

			vertex0.NX = vertex0.NY = vertex0.NZ = 0.0f;
			vertex0.TX = vertex0.TY = vertex0.TZ = 0.0f;
			vertex0.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex1 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 1) * stride);
			vertex1.X = 0.1f;
			vertex1.Y = 0.0f;
			vertex1.Z = 0.0f;
			vertex1.U = 6.0f;

			vertex1.NX = vertex1.NY = vertex1.NZ = 0.0f;
			vertex1.TX = vertex1.TY = vertex1.TZ = 0.0f;
			vertex1.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex2 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 2) * stride);
			vertex2.X = 0.1f;
			vertex2.Y = 0.1f;
			vertex2.Z = 0.0f;
			vertex2.U = 6.0f;

			vertex2.NX = vertex2.NY = vertex2.NZ = 0.0f;
			vertex2.TX = vertex2.TY = vertex2.TZ = 0.0f;
			vertex2.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex3 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 3) * stride);
			vertex3.X = 0.0f;
			vertex3.Y = 0.1f;
			vertex3.Z = 0.0f;
			vertex3.U = 6.0f;

			vertex3.NX = vertex3.NY = vertex3.NZ = 0.0f;
			vertex3.TX = vertex3.TY = vertex3.TZ = 0.0f;
			vertex3.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex4 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 4) * stride);
			vertex4.X = 0.0f;
			vertex4.Y = 0.0f;
			vertex4.Z = 0.1f;
			vertex4.U = 6.0f;


			vertex4.NX = vertex4.NY = vertex4.NZ = 0.0f;
			vertex4.TX = vertex4.TY = vertex4.TZ = 0.0f;
			vertex4.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex5 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 5) * stride);
			vertex5.X = 0.1f;
			vertex5.Y = 0.0f;
			vertex5.Z = 0.1f;
			vertex5.U = 6.0f;

			vertex5.NX = vertex5.NY = vertex5.NZ = 0.0f;
			vertex5.TX = vertex5.TY = vertex5.TZ = 0.0f;
			vertex5.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex6 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 6) * stride);
			vertex6.X = 0.1f;
			vertex6.Y = 0.1f;
			vertex6.Z = 0.1f;
			vertex6.U = 6.0f;

			vertex6.NX = vertex6.NY = vertex6.NZ = 0.0f;
			vertex6.TX = vertex6.TY = vertex6.TZ = 0.0f;
			vertex6.V = 0.0f;

			Mesh_Vertex_Data_Definition& vertex7 =
				*(Mesh_Vertex_Data_Definition*)(vertex_data + (start_vertex_index + 7) * stride);
			vertex7.X = 0.0f;
			vertex7.Y = 0.1f;
			vertex7.Z = 0.1f;
			vertex7.U = 6.0f;

			vertex7.NX = vertex7.NY = vertex7.NZ = 0.0f;
			vertex7.TX = vertex7.TY = vertex7.TZ = 0.0f;
			vertex7.V = 0.0f;
		}

		// index
		size_t index_data_size = (((2 * segments + 12) * 3) * 3 + 3 * 2 * 6) * sizeof(uint16_t);
		this->Mesh_Data.Static_Mesh_Data.Index_Buffer = std::make_shared<Buffer_Data>(index_data_size);
		uint16_t* index_data = static_cast<uint16_t*>(this->Mesh_Data.Static_Mesh_Data.Index_Buffer->Data);

		for (int i = 0; i < segments; ++i)
		{
			index_data[0 * segments * 3 + i * 6 + 0] = (uint16_t)(0 * segments + i);
			index_data[0 * segments * 3 + i * 6 + 1] = (uint16_t)(1 * segments + i);
			index_data[0 * segments * 3 + i * 6 + 2] = (uint16_t)(1 * segments + ((i + 1) % segments));

			index_data[0 * segments * 3 + i * 6 + 3] = (uint16_t)(1 * segments + ((i + 1) % segments));
			index_data[0 * segments * 3 + i * 6 + 4] = (uint16_t)(0 * segments + ((i + 1) % segments));
			index_data[0 * segments * 3 + i * 6 + 5] = (uint16_t)(0 * segments + i);
		}
		{
			index_data[2 * segments * 3 + 0 * 3 + 0] = (uint16_t)(2 * segments + 0);
			index_data[2 * segments * 3 + 0 * 3 + 1] = (uint16_t)(2 * segments + 1);
			index_data[2 * segments * 3 + 0 * 3 + 2] = (uint16_t)(2 * segments + 3);
			index_data[2 * segments * 3 + 1 * 3 + 0] = (uint16_t)(2 * segments + 3);
			index_data[2 * segments * 3 + 1 * 3 + 1] = (uint16_t)(2 * segments + 2);
			index_data[2 * segments * 3 + 1 * 3 + 2] = (uint16_t)(2 * segments + 0);

			index_data[2 * segments * 3 + 2 * 3 + 0] = (uint16_t)(2 * segments + 1);
			index_data[2 * segments * 3 + 2 * 3 + 1] = (uint16_t)(2 * segments + 5);
			index_data[2 * segments * 3 + 2 * 3 + 2] = (uint16_t)(2 * segments + 7);
			index_data[2 * segments * 3 + 3 * 3 + 0] = (uint16_t)(2 * segments + 7);
			index_data[2 * segments * 3 + 3 * 3 + 1] = (uint16_t)(2 * segments + 3);
			index_data[2 * segments * 3 + 3 * 3 + 2] = (uint16_t)(2 * segments + 1);

			index_data[2 * segments * 3 + 4 * 3 + 0] = (uint16_t)(2 * segments + 5);
			index_data[2 * segments * 3 + 4 * 3 + 1] = (uint16_t)(2 * segments + 4);
			index_data[2 * segments * 3 + 4 * 3 + 2] = (uint16_t)(2 * segments + 6);
			index_data[2 * segments * 3 + 5 * 3 + 0] = (uint16_t)(2 * segments + 6);
			index_data[2 * segments * 3 + 5 * 3 + 1] = (uint16_t)(2 * segments + 7);
			index_data[2 * segments * 3 + 5 * 3 + 2] = (uint16_t)(2 * segments + 5);

			index_data[2 * segments * 3 + 6 * 3 + 0] = (uint16_t)(2 * segments + 4);
			index_data[2 * segments * 3 + 6 * 3 + 1] = (uint16_t)(2 * segments + 0);
			index_data[2 * segments * 3 + 6 * 3 + 2] = (uint16_t)(2 * segments + 2);
			index_data[2 * segments * 3 + 7 * 3 + 0] = (uint16_t)(2 * segments + 2);
			index_data[2 * segments * 3 + 7 * 3 + 1] = (uint16_t)(2 * segments + 6);
			index_data[2 * segments * 3 + 7 * 3 + 2] = (uint16_t)(2 * segments + 4);

			index_data[2 * segments * 3 + 8 * 3 + 0] = (uint16_t)(2 * segments + 4);
			index_data[2 * segments * 3 + 8 * 3 + 1] = (uint16_t)(2 * segments + 5);
			index_data[2 * segments * 3 + 8 * 3 + 2] = (uint16_t)(2 * segments + 1);
			index_data[2 * segments * 3 + 9 * 3 + 0] = (uint16_t)(2 * segments + 1);
			index_data[2 * segments * 3 + 9 * 3 + 1] = (uint16_t)(2 * segments + 0);
			index_data[2 * segments * 3 + 9 * 3 + 2] = (uint16_t)(2 * segments + 4);

			index_data[2 * segments * 3 + 10 * 3 + 0] = (uint16_t)(2 * segments + 2);
			index_data[2 * segments * 3 + 10 * 3 + 1] = (uint16_t)(2 * segments + 3);
			index_data[2 * segments * 3 + 10 * 3 + 2] = (uint16_t)(2 * segments + 7);
			index_data[2 * segments * 3 + 11 * 3 + 0] = (uint16_t)(2 * segments + 7);
			index_data[2 * segments * 3 + 11 * 3 + 1] = (uint16_t)(2 * segments + 6);
			index_data[2 * segments * 3 + 11 * 3 + 2] = (uint16_t)(2 * segments + 2);
		}

		for (uint16_t i = 0; i < (2 * segments + 12) * 3; ++i)
		{
			index_data[(2 * segments + 12) * 3 * 1 + i] = (uint16_t)((2 * segments + 8) * 1 + index_data[i]);
			index_data[(2 * segments + 12) * 3 * 2 + i] = (uint16_t)((2 * segments + 8) * 2 + index_data[i]);
		}

		int start_index = ((2 * segments + 12) * 3) * 3;
		index_data[start_index + 0 * 3 + 0] = (uint16_t)(start_vertex_index + 0);
		index_data[start_index + 0 * 3 + 1] = (uint16_t)(start_vertex_index + 1);
		index_data[start_index + 0 * 3 + 2] = (uint16_t)(start_vertex_index + 2);
		index_data[start_index + 1 * 3 + 0] = (uint16_t)(start_vertex_index + 0);
		index_data[start_index + 1 * 3 + 1] = (uint16_t)(start_vertex_index + 2);
		index_data[start_index + 1 * 3 + 2] = (uint16_t)(start_vertex_index + 3);

		index_data[start_index + 2 * 3 + 0] = (uint16_t)(start_vertex_index + 4);
		index_data[start_index + 2 * 3 + 1] = (uint16_t)(start_vertex_index + 5);
		index_data[start_index + 2 * 3 + 2] = (uint16_t)(start_vertex_index + 6);
		index_data[start_index + 3 * 3 + 0] = (uint16_t)(start_vertex_index + 4);
		index_data[start_index + 3 * 3 + 1] = (uint16_t)(start_vertex_index + 6);
		index_data[start_index + 3 * 3 + 2] = (uint16_t)(start_vertex_index + 7);

		index_data[start_index + 4 * 3 + 0] = (uint16_t)(start_vertex_index + 0);
		index_data[start_index + 4 * 3 + 1] = (uint16_t)(start_vertex_index + 1);
		index_data[start_index + 4 * 3 + 2] = (uint16_t)(start_vertex_index + 5);
		index_data[start_index + 5 * 3 + 0] = (uint16_t)(start_vertex_index + 0);
		index_data[start_index + 5 * 3 + 1] = (uint16_t)(start_vertex_index + 5);
		index_data[start_index + 5 * 3 + 2] = (uint16_t)(start_vertex_index + 4);

		index_data[start_index + 6 * 3 + 0] = (uint16_t)(start_vertex_index + 3);
		index_data[start_index + 6 * 3 + 1] = (uint16_t)(start_vertex_index + 2);
		index_data[start_index + 6 * 3 + 2] = (uint16_t)(start_vertex_index + 6);
		index_data[start_index + 7 * 3 + 0] = (uint16_t)(start_vertex_index + 3);
		index_data[start_index + 7 * 3 + 1] = (uint16_t)(start_vertex_index + 6);
		index_data[start_index + 7 * 3 + 2] = (uint16_t)(start_vertex_index + 7);

		index_data[start_index + 8 * 3 + 0] = (uint16_t)(start_vertex_index + 4);
		index_data[start_index + 8 * 3 + 1] = (uint16_t)(start_vertex_index + 5);
		index_data[start_index + 8 * 3 + 2] = (uint16_t)(start_vertex_index + 1);
		index_data[start_index + 9 * 3 + 0] = (uint16_t)(start_vertex_index + 1);
		index_data[start_index + 9 * 3 + 1] = (uint16_t)(start_vertex_index + 0);
		index_data[start_index + 9 * 3 + 2] = (uint16_t)(start_vertex_index + 4);

		index_data[start_index + 10 * 3 + 0] = (uint16_t)(start_vertex_index + 2);
		index_data[start_index + 10 * 3 + 1] = (uint16_t)(start_vertex_index + 3);
		index_data[start_index + 10 * 3 + 2] = (uint16_t)(start_vertex_index + 7);
		index_data[start_index + 11 * 3 + 0] = (uint16_t)(start_vertex_index + 7);
		index_data[start_index + 11 * 3 + 1] = (uint16_t)(start_vertex_index + 6);
		index_data[start_index + 11 * 3 + 2] = (uint16_t)(start_vertex_index + 2);
	}
}// namespace NameSpace_Editor