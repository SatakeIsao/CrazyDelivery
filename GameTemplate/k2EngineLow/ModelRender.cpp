#include "k2EngineLowPreCompile.h"
#include "ModelRender.h"

namespace nsK2EngineLow {

	ModelRender::ModelRender()
	{
		//�R���X�g���N�^�̏���
	}

	ModelRender::~ModelRender()
	{
		// �f�X�g���N�^�̏���
	}

	void ModelRender::Init(
		const char* tkmFilePath,
		AnimationClip* animationClips,
		int numAnimationClips,
		EnModelUpAxis enModelUpAcxis,
		bool isShadowCaster,
		bool isShadowReceiver)
	{
		//�X�P���g����������
		InitSkeleton(tkmFilePath);
		//�A�j���[�V�������������B
		InitAnimation(animationClips, numAnimationClips, enModelUpAcxis);
		//���f���̏�����
		ModelInitData initData;

		initData.m_tkmFilePath = tkmFilePath;

		initData.m_fxFilePath = "Assets/shader/testModel.fx";
		//initData.m_fxFilePath = "Assets/shader/shadowReceiverModel.fx";

		initData.m_expandConstantBuffer = &g_sceneLight->GetLightData();

		initData.m_expandConstantBufferSize = sizeof(g_sceneLight->GetLightData());
	
		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		initData.m_vsEntryPointFunc = "VSMain";
	
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		initData.m_vsSkinEntryPointFunc = "VSSkinMain";
		
		if (isShadowCaster == true)
		{
			InitShadowModel(tkmFilePath, enModelUpAcxis);
		}

		if (isShadowReceiver == true)
		{
			initData.m_psEntryPointFunc = "PSShadowReceverMain";

			initData.m_expandShaderResoruceView[0] =
				&(g_renderingEngine->GetShadowMap().GetRenderTargetTexture());
		}
		else
		{
			initData.m_psEntryPointFunc = "PSNormalMain";
		}
		if (animationClips != nullptr) {
			initData.m_skeleton = &m_skeleton;
		}

		m_model.Init(initData);
	}

	void ModelRender::InitShadowModel(const char* tkmFilePath, EnModelUpAxis modelUpAxis)
	{
		ModelInitData shadowInitData;
		shadowInitData.m_tkmFilePath = tkmFilePath;
		shadowInitData.m_modelUpAxis = modelUpAxis;
		shadowInitData.m_fxFilePath = "Assets/shader/sampleDrawShadowMap.fx";
		shadowInitData.m_colorBufferFormat[0] = DXGI_FORMAT_R32_FLOAT;

		//�X�P���g�����w�肷��
		if (m_animationClips != nullptr)
		{
			shadowInitData.m_skeleton = &m_skeleton;
		}
	
		//�m���X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w�肷��
		shadowInitData.m_vsEntryPointFunc = "VSMain";
		
		//�X�L�����b�V���p�̒��_�V�F�[�_�[�̃G���g���[�|�C���g���w��B
		shadowInitData.m_vsSkinEntryPointFunc = "VSSkinMain";
		m_shadowModel.Init(shadowInitData);
	}

	void ModelRender::InitSkeleton(const char* tkmFilePath)
	{
		//�X�P���g���̃f�[�^��ǂݍ��݁B
		std::string skeletonFilePath = tkmFilePath;
		int pos = (int)skeletonFilePath.find(".tkm");
		skeletonFilePath.replace(pos, 4, ".tks");
		m_skeleton.Init(skeletonFilePath.c_str());
	}

	void ModelRender::InitAnimation(AnimationClip* animationClips, int numAnimationClips,EnModelUpAxis EnModelUpAxis)
	{
		m_animationClips = animationClips;
		m_numAnimationClips = numAnimationClips;
		if (m_animationClips != nullptr)
		{
			m_animation.Init(
				m_skeleton,
				m_animationClips,
				numAnimationClips
			);
		}
	}

	/*void ModelRender::InitComputeAnimationVertexBuffer(const char* tkmFilePath, EnModelUpAxis enModelUpAxis)
	{
		StructuredBuffer* worldMatrxiArraySB = nullptr;
		if (m_isEnableInstancingDraw) {
			worldMatrxiArraySB = &m_worldMatrixArraySB;
		}

		m_computeAnimationVertexBuffer.Init(
			tkmFilePath,
			m_skeleton.GetNumBones(),
			m_skeleton.GetBoneMatricesTopAddress(),
			enModelUpAxis,
			m_maxInstance,
			worldMatrxiArraySB
		);
	}*/

	void ModelRender::Update()
	{
		//���f���̃��[���h�s��X�V
		m_model.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_shadowModel.UpdateWorldMatrix(m_position, m_rotation, m_scale);
		m_skeleton.Update(m_model.GetWorldMatrix());
		//�A�j���[�V������i�߂�
		m_animation.Progress(g_gameTime->GetFrameDeltaTime() * m_animationSpeed);
	}

	void ModelRender::Draw(RenderContext& rc)
	{
		g_renderingEngine->AddRenderObject(this);
	}

	void ModelRender::OnRenderShadowMap(RenderContext& rc, const Matrix& lvpMatrix)
	{
		m_shadowModel.Draw(
			rc,
			g_matIdentity,
			lvpMatrix,
			1
		);
	}

	void ModelRender::OnRenderModel(RenderContext& rc)
	{
		m_model.Draw(rc);
		
	}


	

}