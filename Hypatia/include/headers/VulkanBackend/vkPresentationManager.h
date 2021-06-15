﻿#pragma once
#include "VulkanBackend/vkDeviceManager.h"
#include "VulkanBackend/vkData.h"
namespace hyp_vlk
{
	namespace hyp_backend {
		class PresentationSystem {
			friend class DeviceSystem;
		public:
			PresentationSystem();

			static void CreateWin32Surface(WindowData* windowData, DeviceData* deviceData);
			static void CreateSwapChain(DeviceData* deviceData, ImageData* imageData, WindowData* windowData);
			static void CreateImageBuffer(DeviceData* deviceData, ImageData* imageData);

		private:
			static VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
			static SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
			static VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
			static VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);

		};
	}
} 