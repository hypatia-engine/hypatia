﻿#pragma once
#include "pch.h"
#include "vulkanBackend/vkBufferFactory.h"
#include "VulkanBackend/vkRenderer.h"

namespace hyp_backend {
	struct Vertex {
		glm::vec2 pos;
		glm::vec3 color;

		static VkVertexInputBindingDescription getBindingDescription() {
			VkVertexInputBindingDescription bindingDescription{};
			bindingDescription.binding = 0;
			bindingDescription.stride = sizeof(Vertex);
			bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;

			return bindingDescription;
		}

		static std::array<VkVertexInputAttributeDescription, 2> getAttributeDescriptions() {
			std::array<VkVertexInputAttributeDescription, 2> attributeDescriptions{};

			attributeDescriptions[0].binding = 0;
			attributeDescriptions[0].location = 0;
			attributeDescriptions[0].format = VK_FORMAT_R32G32_SFLOAT;
			attributeDescriptions[0].offset = offsetof(Vertex, pos);

			attributeDescriptions[1].binding = 0;
			attributeDescriptions[1].location = 1;
			attributeDescriptions[1].format = VK_FORMAT_R32G32B32_SFLOAT;
			attributeDescriptions[1].offset = offsetof(Vertex, color);

			return attributeDescriptions;
		}
	};

	class Model {
	public:
		Model();
		const std::vector<Vertex> m_Vertices = {
			{{-0.5f, -0.5f}, {1.0f, 0.0f, 1.0f}},
			{{0.5f, -0.5f}, {0.0f, 1.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
			{{-0.5f, 0.5f}, {1.0f, 1.0f, 1.0f}}
		};

		const std::vector<uint16_t> m_Indices = {
			0, 1, 2, 2, 3, 0
		};

		void Load();
		void CreateVertexBuffer();
		void CreateIndexBuffer();
		VkBuffer GetVertexBuffer() { return m_VertexBuffer; }
		std::vector<Vertex> GetVertexData() { return m_Vertices; }
		VkBuffer m_VertexBuffer;
		VkBuffer m_IndexBuffer;
		private:
			void CopyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
			VkDeviceMemory m_VertexBufferMemory;

			VkDeviceMemory m_IndexBufferMemory;
	};
}