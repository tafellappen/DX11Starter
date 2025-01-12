#pragma once

#include "DXCore.h"
#include "DX12Helper.h"
#include <DirectXMath.h>
#include <wrl/client.h> // Used for ComPtr - a smart pointer for COM objects
#include <memory>
#include "Camera.h"
#include "Mesh.h"
#include "GameEntity.h"
#include "Material.h"
#include "BufferStructs.h"
#include "Lights.h"

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);

private:

	// Should we use vsync to limit the frame rate?
	bool vsync;

	// Initialization helper methods - feel free to customize, combine, etc.
	void CreateRootSigAndPipelineState();
	void CreateBasicGeometry();
	void CreateEntities();
	void CreateMeshes();
	void PlaceEntities();
	void LoadTextures();
	void CreateMaterials();
	
	//for raytracing
	void CreateAccelerationStructures();

	void RandomLighting();
	Light RandomPointLight(float minRange, float maxRange, float minIntensity, float maxIntensity);


	// Note the usage of ComPtr below
	//  - This is a smart pointer for objects that abide by the
	//    Component Object Model, which DirectX objects do
	//  - More info here: https://github.com/Microsoft/DirectXTK/wiki/ComPtr

	// Buffers to hold actual geometry data
	Microsoft::WRL::ComPtr<ID3D12RootSignature> rootSignature;
	Microsoft::WRL::ComPtr<ID3D12PipelineState> pipelineState;
	Microsoft::WRL::ComPtr<ID3D12Resource> vertexBuffer;
	Microsoft::WRL::ComPtr<ID3D12Resource> indexBuffer;
	D3D12_VERTEX_BUFFER_VIEW vbView;
	D3D12_INDEX_BUFFER_VIEW ibView;

	std::shared_ptr<Camera> camera;
	std::vector<std::shared_ptr<GameEntity>> entities;
	std::vector<std::shared_ptr<Mesh>> meshes;
	//std::shared_ptr<Material> material;
	std::vector<std::shared_ptr<Material>> materials;

	//Light lights[128];

	std::vector<Light> lights;
	int lightCount;

	bool raytracing;
	
};

