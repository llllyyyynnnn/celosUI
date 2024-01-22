/*
#pragma once

#include "../../external/imgui/imgui.h"

namespace celosia::resources {

    inline ID3D11Texture2D* tex = nullptr;
    void load_texture(std::string file_path) {

        D3D11_TEXTURE2D_DESC ImageTextureDesc = {};

        ImageTextureDesc.Width = 400;
        ImageTextureDesc.Height = 400;
        ImageTextureDesc.MipLevels = 1;
        ImageTextureDesc.ArraySize = 1;
        ImageTextureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
        ImageTextureDesc.SampleDesc.Count = 1;
        ImageTextureDesc.SampleDesc.Quality = 0;
        ImageTextureDesc.Usage = D3D11_USAGE_IMMUTABLE;
        ImageTextureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

        D3D11_SUBRESOURCE_DATA ImageSubresourceData = {};

        ImageSubresourceData.pSysMem = ImageData;
        ImageSubresourceData.SysMemPitch = ImagePitch;


       // celosia::D3D::device->CreateTexture2D(&ImageTextureDesc, 0, &tex);
    }
}
*/