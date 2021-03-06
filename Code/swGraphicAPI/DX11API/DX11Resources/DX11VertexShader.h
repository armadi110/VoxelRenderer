#pragma once

#include "swGraphicAPI/Resources/MeshResources.h"
#include "DX11Initializer/DX11APIObjects.h"


/**@brief Implementacja vertex shadera w DirectX 11.
@ingroup DX11API*/
class DX11VertexShader	:	public VertexShader, protected DX11APIObjects
{
	RTTR_ENABLE( VertexShader );
private:
	ID3D11VertexShader*				m_vertexShader;
protected:
	~DX11VertexShader();
public:
	DX11VertexShader( ID3D11VertexShader* shader );

	inline ID3D11VertexShader*		Get()					{ return m_vertexShader; }


	virtual bool					ReloadFromFile			() override;
	virtual bool					ReloadFromBinFile		() override;
	virtual void					SaveShaderBinFile		( const std::wstring& fileName ) override;

	static DX11VertexShader*		CreateFromFile			( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_5_0" );
	static DX11VertexShader*		CreateFromFile			( const std::wstring& fileName,
															  const std::string& shaderName,
															  ShaderInputLayout** layout,
															  InputLayoutDescriptor* layout_desc,
															  const char* shaderModel = "vs_5_0" );
	static DX11VertexShader*		CreateFromBinFile		( const std::wstring& fileName, const std::string& shaderName, const char* shaderModel = "vs_4_0" );

	void							SetFileName				( const std::wstring& fileName ) { m_shaderFile = fileName; }
	void							SetShaderName			( const std::string& shaderName ) { m_shaderEntry = shaderName; }
};

