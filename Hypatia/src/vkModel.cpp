﻿#include "vulkanBackend/vkModel.h"

namespace hyp_backend {

	Model::Model()
	{
		createVertexBuffer();
	}

	void Model::Load()
	{

	}

	void Model::createVertexBuffer() {
		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = sizeof(m_Vertices[0]) * m_Vertices.size();
		bufferInfo.usage = VK_BUFFER_USAGE_VERTEX_BUFFER_BIT;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		if (vkCreateBuffer(RendererBackend::GetDevice(), &bufferInfo, nullptr, &m_VertexBuffer) != VK_SUCCESS) {
			throw std::runtime_error("failed to create vertex buffer!");
		}

		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(RendererBackend::GetDevice(), m_VertexBuffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = FindMemoryType(memRequirements.memoryTypeBits, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);

		if (vkAllocateMemory(RendererBackend::GetDevice(), &allocInfo, nullptr, &m_VertexBufferMemory) != VK_SUCCESS) {
			throw std::runtime_error("failed to allocate vertex buffer memory!");
		}

		vkBindBufferMemory(RendererBackend::GetDevice(), m_VertexBuffer, m_VertexBufferMemory, 0);

		void* data;
		vkMapMemory(RendererBackend::GetDevice(), m_VertexBufferMemory, 0, bufferInfo.size, 0, &data);
		memcpy(data, m_Vertices.data(), (size_t)bufferInfo.size);
		vkUnmapMemory(RendererBackend::GetDevice(), m_VertexBufferMemory);
	}

	uint32_t Model::FindMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties) {
		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(RendererBackend::GetPhysicalDevice(), &memProperties);

		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}

		throw std::runtime_error("failed to find suitable memory type!");
	}
}