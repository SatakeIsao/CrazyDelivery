#pragma once
#include "Shadow.h"
#include "Bloom.h"

namespace nsK2EngineLow {

	class Bloom;
	class SpriteRender;
	class FontRender;

	class RenderingEngine : public Noncopyable
	{
	public:
		RenderingEngine();
		~RenderingEngine();

		void Init();
		void InitShadowMap();
		void InitBloomLumi();
		void InitBloomGauss();
		void InitBloomBoke();
		
		void AddRenderObject(IRenderer* renderObject)
		{
			m_renderObjects.emplace_back(renderObject);
		}

		/// <summary>
		/// �X�v���C�g�����_�[���R���e�i�̌��ɂ�������
		/// </summary>
		/// <param name="spriteRender">�X�v���C�g�����_�[</param>
		void AddSpriteRenderObject(SpriteRender* spriteRender)
		{
			SpriteRenderObject.push_back(spriteRender);
		}
		/// <summary>
		/// �t�H���g�����_�[���R���e�i�̌��ɂ�������
		/// </summary>
		/// <param name="fontRender">�t�H���g�����_�[</param>
		void AddFontRenderObject(FontRender* fontRender)
		{
			FontRenderObject.push_back(fontRender);
		}

		//void InitFinalSprite();
		//���f���̕`��
		void ModelDraw(RenderContext& rc);
		//2D���f���̕`��
		void Render2DSprite(RenderContext& rc);
		//���O2D���f���̕`��
		//void PreRender2D(RenderContext& rc);
		//�V���h�E�}�b�v�`�揈��
		void RenderShadowDraw(RenderContext& rc);
		//���s
		void Execute(RenderContext& rc);

		void CopyMainRenderTargetFrameBuffer(RenderContext& rc);

		////���C�g�r���[�X�N���[���̐ݒ�
		//void SetLVP(Matrix mat)
		//{
		//	m_sceneLight.SetLVP(mat);
		//}
		//�擾�n�̊֐�
		SceneLight& GetLightingCB()
		{
			return m_sceneLight;
		}


		RenderTarget& GetShadowMap()
		{
			return shadow.GetRenderTarget();
		}

		Camera& GetLigCamera()
		{
			return shadow.GetLigCamera();
		}

		RenderTarget& GetBloom()
		{
			return bloom.GetRenderTarget();
		}

	private:
		SceneLight m_sceneLight;
		RenderTarget m_mainRenderingTarget;
		//�V���h�E�p
		//RenderTarget m_shadowMapTarget;
		Camera lightCamera;
		Shadow shadow;
		//�u���[���p
		Bloom bloom;
		//RenderTarget* luminanceRenderTarget;
		Sprite m_copyToFrameBufferSprite;
		SpriteInitData m_spriteInitData;

		std::vector<ModelRender*> ModelRenderObject;
		std::vector<IRenderer* > m_renderObjects;	//�`��I�u�W�F�N�g�̃��X�g
		std::vector<SpriteRender*> SpriteRenderObject;	//�X�v���C�g�����_�[
		std::vector<FontRender*> FontRenderObject;	//�t�H���g�����_�[
	};

}

