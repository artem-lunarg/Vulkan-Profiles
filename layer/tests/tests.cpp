#include <vulkan/vulkan_core.h>

#include <gtest/gtest.h>
#include "profiles_test_helper.h"

#ifdef _WIN32
#ifdef _DEBUG
static const char* CONFIG_PATH = "bin/Debug";
#else
static const char* CONFIG_PATH = "bin/Release";
#endif
#else 
static const char* CONFIG_PATH = "lib";
#endif

TEST(layer, TestDesktopPortability2022Limits) {
    VkResult err = VK_SUCCESS;

    const std::string layer_path = std::string(TEST_BINARY_PATH) + CONFIG_PATH;
    profiles_test::setEnvironmentSetting("VK_LAYER_PATH", layer_path.c_str());

    profiles_test::VulkanInstanceBuilder inst_builder;

    const std::string filepath = TEST_SOURCE_PATH "/../../profiles/VP_LUNARG_desktop_portability_2021.json";
    profiles_test::setProfilesFilename(filepath);
    profiles_test::setProfilesProfileName("VP_LUNARG_desktop_portability_2021");
    profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
    profiles_test::setProfilesFailOnError(false);

    inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");

    err = inst_builder.makeInstance();
    ASSERT_EQ(err, VK_SUCCESS);

    VkInstance test_inst = inst_builder.getInstance();

    VkPhysicalDevice gpu;
    err = inst_builder.getPhysicalDevice(&gpu);
    if (err != VK_SUCCESS) {
        printf("Profile not supported on device, skipping test.\n");
        vkDestroyInstance(test_inst, nullptr);
        return;
    }

    VkPhysicalDeviceProperties gpu_props{};
    vkGetPhysicalDeviceProperties(gpu, &gpu_props);

    VkPhysicalDeviceFeatures gpu_feats{};
    vkGetPhysicalDeviceFeatures(gpu, &gpu_feats);

    VkPhysicalDeviceMemoryProperties gpu_mem_props{};
    vkGetPhysicalDeviceMemoryProperties(gpu, &gpu_mem_props);

    uint32_t queue_family_count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count, nullptr);
    std::vector<VkQueueFamilyProperties> queue_family_props(queue_family_count);
    vkGetPhysicalDeviceQueueFamilyProperties(gpu, &queue_family_count, queue_family_props.data());

    // Limits
    EXPECT_GE(gpu_props.limits.maxImageDimension1D, 16384u);
    EXPECT_GE(gpu_props.limits.maxImageDimension2D, 16384u);
    EXPECT_GE(gpu_props.limits.maxImageDimension3D, 2048u);
    EXPECT_GE(gpu_props.limits.maxImageDimensionCube, 16384u);
    EXPECT_GE(gpu_props.limits.maxImageArrayLayers, 2048u);
    EXPECT_GE(gpu_props.limits.maxTexelBufferElements, 67108864u);
    EXPECT_GE(gpu_props.limits.maxUniformBufferRange, 65536u);
    EXPECT_GE(gpu_props.limits.maxStorageBufferRange, 134217728u);
    EXPECT_GE(gpu_props.limits.maxPushConstantsSize, 128u);
    EXPECT_GE(gpu_props.limits.maxMemoryAllocationCount, 4096u);
    EXPECT_GE(gpu_props.limits.maxSamplerAllocationCount, 1024u);
    EXPECT_LE(gpu_props.limits.bufferImageGranularity, 1024);
    EXPECT_GE(gpu_props.limits.maxBoundDescriptorSets, 8u);
    EXPECT_GE(gpu_props.limits.maxPerStageDescriptorSamplers, 16u);
    EXPECT_GE(gpu_props.limits.maxPerStageDescriptorUniformBuffers, 15u);
    EXPECT_GE(gpu_props.limits.maxPerStageDescriptorStorageBuffers, 16u);
    EXPECT_GE(gpu_props.limits.maxPerStageDescriptorSampledImages, 128u);
    EXPECT_GE(gpu_props.limits.maxPerStageDescriptorStorageImages, 8u);
    EXPECT_GE(gpu_props.limits.maxPerStageDescriptorInputAttachments, 8u);
    EXPECT_GE(gpu_props.limits.maxPerStageResources, 128u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetSamplers, 80u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetUniformBuffers, 90u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetUniformBuffersDynamic, 8u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetStorageBuffers, 155u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetStorageBuffersDynamic, 8u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetSampledImages, 256u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetStorageImages, 40u);
    EXPECT_GE(gpu_props.limits.maxDescriptorSetInputAttachments, 8u);
    EXPECT_GE(gpu_props.limits.maxVertexInputAttributes, 28u);
    EXPECT_GE(gpu_props.limits.maxVertexInputBindings, 28u);
    EXPECT_GE(gpu_props.limits.maxVertexInputAttributeOffset, 2047u);
    EXPECT_GE(gpu_props.limits.maxVertexInputBindingStride, 2048u);
    EXPECT_GE(gpu_props.limits.maxVertexOutputComponents, 124u);
    EXPECT_GE(gpu_props.limits.maxTessellationGenerationLevel, 64u);
    EXPECT_GE(gpu_props.limits.maxTessellationPatchSize, 32u);
    EXPECT_GE(gpu_props.limits.maxTessellationControlPerVertexInputComponents, 124u);
    EXPECT_GE(gpu_props.limits.maxTessellationControlPerVertexOutputComponents, 124u);
    EXPECT_GE(gpu_props.limits.maxTessellationControlPerPatchOutputComponents, 120u);
    EXPECT_GE(gpu_props.limits.maxTessellationControlTotalOutputComponents, 2048u);
    EXPECT_GE(gpu_props.limits.maxTessellationEvaluationInputComponents, 124u);
    EXPECT_GE(gpu_props.limits.maxTessellationEvaluationOutputComponents, 124u);
    EXPECT_GE(gpu_props.limits.maxFragmentInputComponents, 116u);
    EXPECT_GE(gpu_props.limits.maxFragmentOutputAttachments, 8u);
    EXPECT_GE(gpu_props.limits.maxFragmentDualSrcAttachments, 1u);
    EXPECT_GE(gpu_props.limits.maxFragmentCombinedOutputResources, 8u);
    EXPECT_GE(gpu_props.limits.maxComputeSharedMemorySize, 32768u);
    EXPECT_GE(gpu_props.limits.maxComputeWorkGroupCount[0], 65535u);
    EXPECT_GE(gpu_props.limits.maxComputeWorkGroupCount[1], 65535u);
    EXPECT_GE(gpu_props.limits.maxComputeWorkGroupCount[2], 65535u);
    EXPECT_GE(gpu_props.limits.maxComputeWorkGroupInvocations, 1024u);
    EXPECT_GE(gpu_props.limits.maxComputeWorkGroupSize[0], 1024u);
    EXPECT_GE(gpu_props.limits.maxComputeWorkGroupSize[1], 1024u);
    EXPECT_GE(gpu_props.limits.maxComputeWorkGroupSize[2], 64u);
    EXPECT_GE(gpu_props.limits.subPixelPrecisionBits, 4u);
    EXPECT_GE(gpu_props.limits.subTexelPrecisionBits, 4u);
    EXPECT_GE(gpu_props.limits.mipmapPrecisionBits, 4u);
    EXPECT_GE(gpu_props.limits.maxDrawIndexedIndexValue, 429467295u);
    EXPECT_GE(gpu_props.limits.maxDrawIndirectCount, 1073740000u);
    EXPECT_GE(gpu_props.limits.maxSamplerLodBias, 4.0f);
    EXPECT_GE(gpu_props.limits.maxSamplerAnisotropy, 16.0f);
    EXPECT_GE(gpu_props.limits.maxViewports, 16u);
    EXPECT_GE(gpu_props.limits.maxViewportDimensions[0], 16384u);
    EXPECT_GE(gpu_props.limits.maxViewportDimensions[1], 16384u);
    EXPECT_LE(gpu_props.limits.viewportBoundsRange[0], -32768.0f);
    EXPECT_GE(gpu_props.limits.viewportBoundsRange[1], 32767.0f);
    EXPECT_GE(gpu_props.limits.minMemoryMapAlignment, 64u);
    EXPECT_LE(gpu_props.limits.minTexelBufferOffsetAlignment, 64u);
    EXPECT_LE(gpu_props.limits.minUniformBufferOffsetAlignment, 256u);
    EXPECT_LE(gpu_props.limits.minStorageBufferOffsetAlignment, 64u);
    EXPECT_LE(gpu_props.limits.minTexelOffset, -8);
    EXPECT_GE(gpu_props.limits.maxTexelOffset, 7u);
    EXPECT_LE(gpu_props.limits.minTexelGatherOffset, -8);
    EXPECT_GE(gpu_props.limits.maxTexelGatherOffset, 7u);
    EXPECT_LE(gpu_props.limits.minInterpolationOffset, -0.5f);
    EXPECT_GE(gpu_props.limits.maxInterpolationOffset, 0.4375f);
    EXPECT_GE(gpu_props.limits.subPixelInterpolationOffsetBits, 4u);
    EXPECT_GE(gpu_props.limits.maxFramebufferWidth, 16384u);
    EXPECT_GE(gpu_props.limits.maxFramebufferHeight, 16384u);
    EXPECT_GE(gpu_props.limits.maxFramebufferLayers, 1024u);
    EXPECT_EQ(gpu_props.limits.framebufferColorSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_EQ(gpu_props.limits.framebufferColorSampleCounts & VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_4_BIT);
    EXPECT_EQ(gpu_props.limits.framebufferDepthSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_EQ(gpu_props.limits.framebufferDepthSampleCounts & VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_4_BIT);
    EXPECT_EQ(gpu_props.limits.framebufferStencilSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_EQ(gpu_props.limits.framebufferStencilSampleCounts & VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_4_BIT);
    EXPECT_GE(gpu_props.limits.maxColorAttachments, 8u);
    EXPECT_EQ(gpu_props.limits.sampledImageColorSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_EQ(gpu_props.limits.sampledImageColorSampleCounts & VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_4_BIT);
    EXPECT_EQ(gpu_props.limits.sampledImageIntegerSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_EQ(gpu_props.limits.sampledImageIntegerSampleCounts & VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_4_BIT);
    EXPECT_EQ(gpu_props.limits.sampledImageDepthSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_EQ(gpu_props.limits.sampledImageDepthSampleCounts & VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_4_BIT);
    EXPECT_EQ(gpu_props.limits.sampledImageStencilSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_EQ(gpu_props.limits.sampledImageStencilSampleCounts & VK_SAMPLE_COUNT_4_BIT, VK_SAMPLE_COUNT_4_BIT);
    EXPECT_EQ(gpu_props.limits.storageImageSampleCounts & VK_SAMPLE_COUNT_1_BIT, VK_SAMPLE_COUNT_1_BIT);
    EXPECT_LE(gpu_props.limits.maxSampleMaskWords, 1u);
    EXPECT_GE(gpu_props.limits.maxClipDistances, 8u);
    EXPECT_GE(gpu_props.limits.maxCombinedClipAndCullDistances, 8u);
    EXPECT_GE(gpu_props.limits.discreteQueuePriorities, 2u);
    EXPECT_LE(gpu_props.limits.pointSizeRange[0], 1.0f);
    EXPECT_GE(gpu_props.limits.pointSizeRange[1], 64.0f);
    EXPECT_LE(gpu_props.limits.lineWidthRange[0], 1.0f);
    EXPECT_GE(gpu_props.limits.lineWidthRange[1], 1.0f);
    EXPECT_LE(gpu_props.limits.pointSizeGranularity, 1.0f);
    EXPECT_LE(gpu_props.limits.lineWidthGranularity, 0.5f);

    // Features
    EXPECT_EQ(gpu_feats.depthBiasClamp, VK_TRUE);
    EXPECT_EQ(gpu_feats.depthClamp, VK_TRUE);
    EXPECT_EQ(gpu_feats.drawIndirectFirstInstance, VK_TRUE);
    EXPECT_EQ(gpu_feats.dualSrcBlend, VK_TRUE);
    EXPECT_EQ(gpu_feats.fillModeNonSolid, VK_TRUE);
    EXPECT_EQ(gpu_feats.fragmentStoresAndAtomics, VK_TRUE);
    EXPECT_EQ(gpu_feats.fullDrawIndexUint32, VK_TRUE);
    EXPECT_EQ(gpu_feats.imageCubeArray, VK_TRUE);
    EXPECT_EQ(gpu_feats.independentBlend, VK_TRUE);
    EXPECT_EQ(gpu_feats.inheritedQueries, VK_TRUE);
    EXPECT_EQ(gpu_feats.largePoints, VK_TRUE);
    EXPECT_EQ(gpu_feats.multiDrawIndirect, VK_TRUE);
    EXPECT_EQ(gpu_feats.multiViewport, VK_TRUE);
    EXPECT_EQ(gpu_feats.occlusionQueryPrecise, VK_TRUE);
    EXPECT_EQ(gpu_feats.robustBufferAccess, VK_TRUE);
    EXPECT_EQ(gpu_feats.sampleRateShading, VK_TRUE);
    EXPECT_EQ(gpu_feats.samplerAnisotropy, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderClipDistance, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderImageGatherExtended, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderSampledImageArrayDynamicIndexing, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderStorageBufferArrayDynamicIndexing, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderStorageImageArrayDynamicIndexing, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderStorageImageExtendedFormats, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderStorageImageWriteWithoutFormat, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderTessellationAndGeometryPointSize, VK_TRUE);
    EXPECT_EQ(gpu_feats.shaderUniformBufferArrayDynamicIndexing, VK_TRUE);
    EXPECT_EQ(gpu_feats.tessellationShader, VK_TRUE);
    EXPECT_EQ(gpu_feats.textureCompressionBC, VK_TRUE);
    EXPECT_EQ(gpu_feats.vertexPipelineStoresAndAtomics, VK_TRUE);

    vkDestroyInstance(test_inst, nullptr);
}

TEST(layer, TestSetCombinationMode) {
    VkResult err = VK_SUCCESS;

    const std::string layer_path = std::string(TEST_BINARY_PATH) + CONFIG_PATH;
    profiles_test::setEnvironmentSetting("VK_LAYER_PATH", layer_path.c_str());

    profiles_test::VulkanInstanceBuilder inst_builder;

    std::vector<VkExtensionProperties> device_extensions;
    {
        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);

        if (err != VK_SUCCESS) {
            printf("Profile not supported on device, skipping test.\n");
        } else {
            uint32_t count;
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, nullptr);
            device_extensions.resize(count);
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, device_extensions.data());
        }

        vkDestroyInstance(test_inst, nullptr);
        inst_builder.reset();
    }

    {
        inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");
        const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_api.json";
        profiles_test::setProfilesFilename(filepath);
        profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
        profiles_test::setProfilesProfileName("VP_LUNARG_test_api");
        profiles_test::setProfilesSimulateCapabilities(0);

        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);

        if (err != VK_SUCCESS) {
            printf("Profile not supported on device, skipping test.\n");
        } else {
            VkPhysicalDeviceProperties gpu_props{};
            vkGetPhysicalDeviceProperties(gpu, &gpu_props);

            VkPhysicalDeviceFeatures gpu_feats{};
            vkGetPhysicalDeviceFeatures(gpu, &gpu_feats);

            uint32_t count;
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, nullptr);
            std::vector<VkExtensionProperties> extensions(count);
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, extensions.data());

            size_t portability_subset_add = 1;
            for (const auto& ext : device_extensions) {
                if (strcmp(ext.extensionName, "VK_KHR_portability_subset") == 0) {
                    portability_subset_add = 0;
                    break;
                }
            }
            ASSERT_EQ(device_extensions.size() + portability_subset_add, extensions.size());
        }

        vkDestroyInstance(test_inst, nullptr);
        inst_builder.reset();
    }

    {
        inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");
        const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_api.json";
        profiles_test::setProfilesFilename(filepath);
        profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
        profiles_test::setProfilesProfileName("VP_LUNARG_test_api_1_2_198");
        profiles_test::setProfilesSimulateCapabilities(profiles_test::SimulateCapabilityFlag::SIMULATE_EXTENSIONS_BIT);
        profiles_test::setProfilesFailOnError(false);

        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);

        if (err != VK_SUCCESS) {
            printf("Profile not supported on device, skipping test.\n");
        } else {
            VkPhysicalDeviceProperties gpu_props{};
            vkGetPhysicalDeviceProperties(gpu, &gpu_props);

            VkPhysicalDeviceFeatures gpu_feats{};
            vkGetPhysicalDeviceFeatures(gpu, &gpu_feats);

            uint32_t count;
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, nullptr);
            std::vector<VkExtensionProperties> extensions(count);
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, extensions.data());

            size_t portability_subset_add = 1;
            for (const auto& ext : device_extensions) {
                if (strcmp(ext.extensionName, "VK_KHR_portability_subset") == 0) {
                    portability_subset_add = 0;
                    break;
                }
            }
            ASSERT_EQ(device_extensions.size() + portability_subset_add, extensions.size());
        }

        vkDestroyInstance(test_inst, nullptr);
        inst_builder.reset();
    }

    {
        inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");
        const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_api.json";
        profiles_test::setProfilesFilename(filepath);
        profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
        profiles_test::setProfilesProfileName("VP_LUNARG_test_api");
        profiles_test::setProfilesSimulateCapabilities(profiles_test::SimulateCapabilityFlag::SIMULATE_EXTENSIONS_BIT);
        profiles_test::setProfilesFailOnError(false);

        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);

        if (err != VK_SUCCESS) {
            printf("Profile not supported on device, skipping test.\n");
        } else {
            VkPhysicalDeviceProperties gpu_props{};
            vkGetPhysicalDeviceProperties(gpu, &gpu_props);

            VkPhysicalDeviceFeatures gpu_feats{};
            vkGetPhysicalDeviceFeatures(gpu, &gpu_feats);

            uint32_t count;
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, nullptr);
            std::vector<VkExtensionProperties> extensions(count);
            vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, extensions.data());

            ASSERT_EQ(extensions.size(), 234);
        }

        vkDestroyInstance(test_inst, nullptr);
        inst_builder.reset();
    }
}

TEST(layer, TestExtensionNotSupported) {
    VkResult err = VK_SUCCESS;

    const std::string layer_path = std::string(TEST_BINARY_PATH) + CONFIG_PATH;
    profiles_test::setEnvironmentSetting("VK_LAYER_PATH", layer_path.c_str());

    profiles_test::VulkanInstanceBuilder inst_builder;

    std::vector<VkExtensionProperties> device_extensions;
    {
        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);
        ASSERT_EQ(err, VK_SUCCESS);

        uint32_t count;
        vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, nullptr);
        device_extensions.resize(count);
        vkEnumerateDeviceExtensionProperties(gpu, nullptr, &count, device_extensions.data());

        vkDestroyInstance(test_inst, nullptr);
        inst_builder.reset();
    }

    {
        inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");
        const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_api.json";
        profiles_test::setProfilesFilename(filepath);
        profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
        profiles_test::setProfilesProfileName("VP_LUNARG_test_api");
        profiles_test::setProfilesSimulateCapabilities(profiles_test::SimulateCapabilityFlag::SIMULATE_EXTENSIONS_BIT);
        profiles_test::setProfilesFailOnError(true);

        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);

        if (device_extensions.size() < 233) {
            ASSERT_EQ(err, VK_ERROR_INITIALIZATION_FAILED);
        }

        vkDestroyInstance(test_inst, nullptr);
        inst_builder.reset();
    }
}

TEST(layer, TestSelectingProfileAndCapabilities) {
    VkResult err = VK_SUCCESS;

    const std::string layer_path = std::string(TEST_BINARY_PATH) + CONFIG_PATH;
    profiles_test::setEnvironmentSetting("VK_LAYER_PATH", layer_path.c_str());

    profiles_test::VulkanInstanceBuilder inst_builder;

    {
        const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_selecting_profile.json";
        profiles_test::setProfilesFilename(filepath);
        profiles_test::setProfilesProfileName("VP_LUNARG_test_selecting_profile");
        profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
        profiles_test::setProfilesSimulateCapabilities(profiles_test::SimulateCapabilityFlag::SIMULATE_EXTENSIONS_BIT |
                                                       profiles_test::SimulateCapabilityFlag::SIMULATE_PROPERTIES_BIT);

        inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");

        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);
        if (err != VK_SUCCESS) {
            printf("Profile not supported on device, skipping test.\n");
            vkDestroyInstance(test_inst, nullptr);
            return;
        }

        VkPhysicalDeviceProperties gpu_props{};
        vkGetPhysicalDeviceProperties(gpu, &gpu_props);

        EXPECT_EQ(gpu_props.limits.maxImageDimension1D, 16384u);

        inst_builder.reset();
    }

    {
        const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_selecting_profile.json";
        profiles_test::setProfilesFilename(filepath);
        profiles_test::setProfilesProfileName("VP_LUNARG_test_selecting_profile_subset");
        profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
        profiles_test::setProfilesSimulateCapabilities(profiles_test::SimulateCapabilityFlag::SIMULATE_EXTENSIONS_BIT |
                                                       profiles_test::SimulateCapabilityFlag::SIMULATE_PROPERTIES_BIT);

        inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");

        err = inst_builder.makeInstance();
        ASSERT_EQ(err, VK_SUCCESS);

        VkInstance test_inst = inst_builder.getInstance();

        VkPhysicalDevice gpu;
        err = inst_builder.getPhysicalDevice(&gpu);
        if (err != VK_SUCCESS) {
            printf("Profile not supported on device, skipping test.\n");
            vkDestroyInstance(test_inst, nullptr);
            return;
        }

        VkPhysicalDeviceProperties gpu_props{};
        vkGetPhysicalDeviceProperties(gpu, &gpu_props);

        EXPECT_EQ(gpu_props.limits.maxImageDimension1D, 4096u);

        inst_builder.reset();
    }
}

TEST(layer, TestParsingAllFormatProperties) {
    VkResult err = VK_SUCCESS;

    const std::string layer_path = std::string(TEST_BINARY_PATH) + CONFIG_PATH;
    profiles_test::setEnvironmentSetting("VK_LAYER_PATH", layer_path.c_str());

    profiles_test::VulkanInstanceBuilder inst_builder;

    const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_formats.json";
    profiles_test::setProfilesFilename(filepath);
    profiles_test::setProfilesProfileName("VP_LUNARG_test_formats");
    profiles_test::setProfilesEmulatePortabilitySubsetExtension(true);
    profiles_test::setProfilesSimulateAllCapabilities();
    profiles_test::setProfilesFailOnError(false);

    inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");

    err = inst_builder.makeInstance();
    ASSERT_EQ(err, VK_SUCCESS);

    VkInstance test_inst = inst_builder.getInstance();

    VkPhysicalDevice gpu;
    err = inst_builder.getPhysicalDevice(&gpu);
    if (err != VK_SUCCESS) {
        printf("Profile not supported on device, skipping test.\n");
        vkDestroyInstance(test_inst, nullptr);
        return;
    }

    {
        VkFormat format = VK_FORMAT_R4G4_UNORM_PACK8;
        VkFormatProperties format_properties;
        vkGetPhysicalDeviceFormatProperties(gpu, format, &format_properties);

        VkFormatFeatureFlags linear_tiling_features = VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT;
        VkFormatFeatureFlags optimal_tiling_features = VK_FORMAT_FEATURE_VERTEX_BUFFER_BIT;
        VkFormatFeatureFlags buffer_features = VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT;

        EXPECT_EQ(format_properties.linearTilingFeatures & linear_tiling_features, linear_tiling_features);
        EXPECT_EQ(format_properties.optimalTilingFeatures & optimal_tiling_features, optimal_tiling_features);
        EXPECT_EQ(format_properties.bufferFeatures & buffer_features, buffer_features);
    }

    {
        VkFormat format = VK_FORMAT_R4G4B4A4_UNORM_PACK16;
        VkFormatProperties2 format_properties2 = {};
        format_properties2.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
        vkGetPhysicalDeviceFormatProperties2(gpu, format, &format_properties2);

        const VkFormatProperties& format_properties = format_properties2.formatProperties;

        VkFormatFeatureFlags linear_tiling_features = VK_FORMAT_FEATURE_SAMPLED_IMAGE_BIT;
        VkFormatFeatureFlags optimal_tiling_features = VK_FORMAT_FEATURE_COLOR_ATTACHMENT_BLEND_BIT;
        VkFormatFeatureFlags buffer_features = VK_FORMAT_FEATURE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR;

        EXPECT_EQ(format_properties.linearTilingFeatures & linear_tiling_features, linear_tiling_features);
        EXPECT_EQ(format_properties.optimalTilingFeatures & optimal_tiling_features, optimal_tiling_features);
        EXPECT_EQ(format_properties.bufferFeatures & buffer_features, buffer_features);
    }

#ifdef VK_KHR_format_feature_flags2
    {
        VkFormat format = VK_FORMAT_B4G4R4A4_UNORM_PACK16;
        VkFormatProperties2 format_properties2 = {};
        format_properties2.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_2;
        VkFormatProperties3 format_properties3 = {};
        format_properties3.sType = VK_STRUCTURE_TYPE_FORMAT_PROPERTIES_3;
        format_properties2.pNext = &format_properties3;
        vkGetPhysicalDeviceFormatProperties2(gpu, format, &format_properties2);

        VkFormatFeatureFlags2KHR linear_tiling_features = VK_FORMAT_FEATURE_2_STORAGE_TEXEL_BUFFER_ATOMIC_BIT_KHR;
        VkFormatFeatureFlags2KHR optimal_tiling_features = VK_FORMAT_FEATURE_2_STORAGE_IMAGE_BIT_KHR;
        VkFormatFeatureFlags2KHR buffer_features = VK_FORMAT_FEATURE_2_COLOR_ATTACHMENT_BLEND_BIT_KHR;

        EXPECT_EQ(format_properties3.linearTilingFeatures & linear_tiling_features, linear_tiling_features);
        EXPECT_EQ(format_properties3.optimalTilingFeatures & optimal_tiling_features, optimal_tiling_features);
        EXPECT_EQ(format_properties3.bufferFeatures & buffer_features, buffer_features);
    }
#endif

    vkDestroyInstance(test_inst, nullptr);
}

TEST(profiles, TestEnumBits) {
#if defined(VK_NV_fragment_shading_rate_enums) && defined(VK_KHR_fragment_shading_rate) && defined(VK_KHR_shader_float_controls)
    VkResult err = VK_SUCCESS;

    const std::string layer_path = std::string(TEST_BINARY_PATH) + CONFIG_PATH;
    profiles_test::setEnvironmentSetting("VK_LAYER_PATH", layer_path.c_str());

    profiles_test::VulkanInstanceBuilder inst_builder;

    const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_api_alternate.json";
    profiles_test::setProfilesFilename(filepath);
    profiles_test::setProfilesProfileName("VP_LUNARG_test_api");
    profiles_test::setProfilesSimulateAllCapabilities();

    inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");

    err = inst_builder.makeInstance();
    ASSERT_EQ(err, VK_SUCCESS);

    VkInstance instance = inst_builder.getInstance();

    VkPhysicalDevice physical_device;
    err = inst_builder.getPhysicalDevice(&physical_device);
    ASSERT_EQ(err, VK_SUCCESS);

    VkPhysicalDevice gpu = VK_NULL_HANDLE;
    err = inst_builder.getPhysicalDevice(&gpu);
    if (gpu == VK_NULL_HANDLE) return;

    VkPhysicalDeviceFragmentShadingRateEnumsPropertiesNV fragment_shading_rate_enums_properties{};
    fragment_shading_rate_enums_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_ENUMS_PROPERTIES_NV;

    VkPhysicalDeviceFragmentShadingRatePropertiesKHR fragment_shading_rate_properties{};
    fragment_shading_rate_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FRAGMENT_SHADING_RATE_PROPERTIES_KHR;
    fragment_shading_rate_properties.pNext = &fragment_shading_rate_enums_properties;

    VkPhysicalDeviceFloatControlsPropertiesKHR float_control_properties{};
    float_control_properties.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FLOAT_CONTROLS_PROPERTIES_KHR;
    float_control_properties.pNext = &fragment_shading_rate_properties;

    VkPhysicalDeviceProperties2 gpu_props{};
    gpu_props.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_PROPERTIES_2;
    gpu_props.pNext = &float_control_properties;
    vkGetPhysicalDeviceProperties2(gpu, &gpu_props);

    EXPECT_EQ(float_control_properties.denormBehaviorIndependence, VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_32_BIT_ONLY);
    EXPECT_EQ(float_control_properties.roundingModeIndependence, VK_SHADER_FLOAT_CONTROLS_INDEPENDENCE_32_BIT_ONLY);

    EXPECT_EQ(fragment_shading_rate_properties.maxFragmentShadingRateRasterizationSamples, VK_SAMPLE_COUNT_2_BIT);

    EXPECT_EQ(fragment_shading_rate_enums_properties.maxFragmentShadingRateInvocationCount, VK_SAMPLE_COUNT_2_BIT);
#endif
}

TEST(profiles, TestDuplicatedMembers) {
    VkResult err = VK_SUCCESS;

    const std::string layer_path = std::string(TEST_BINARY_PATH) + CONFIG_PATH;
    profiles_test::setEnvironmentSetting("VK_LAYER_PATH", layer_path.c_str());

    profiles_test::VulkanInstanceBuilder inst_builder;

    const std::string filepath = TEST_SOURCE_PATH "/../../profiles/test/data/VP_LUNARG_test_duplicated.json";
    profiles_test::setProfilesFilename(filepath);
    profiles_test::setProfilesProfileName("VP_LUNARG_test_duplicated");
    profiles_test::setProfilesSimulateAllCapabilities();
    profiles_test::setProfilesFailOnError(true);

    inst_builder.addLayer("VK_LAYER_KHRONOS_profiles");

    err = inst_builder.makeInstance();
    ASSERT_EQ(err, VK_SUCCESS);

    VkInstance instance = inst_builder.getInstance();

    VkPhysicalDevice physical_device;
    err = inst_builder.getPhysicalDevice(&physical_device);
    ASSERT_EQ(err, VK_ERROR_INITIALIZATION_FAILED);
}
