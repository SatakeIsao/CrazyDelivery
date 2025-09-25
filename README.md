# Crazy Delivery
<img width="1280" height="720" alt="image" src="https://github.com/user-attachments/assets/cee9c30a-6122-44e1-b376-e37444ffb2bf" />

> ### 河原電子ビジネス専門学校 ゲームクリエイター科
> ### 氏名：佐竹 功（さたけ いさお）
>
>  <dt>GitHubのURL</dt>
>  <dd>https://github.com/SatakeIsao/CrazyDelivery</dd> 
>
>  <dt>YouTubeのURL</dt>
>  <dd>https://youtu.be/ah3JRHyyDHI</dd>


# 目次
- [Crazy Delivery](#crazy-delivery)
- [目次](#目次)
- [作品概要](#作品概要)
- [担当ソースコード](#担当ソースコード)
- [操作説明](#操作説明)
- [ゲーム説明](#ゲーム説明)
  - [◇ゲーム詳細](#ゲーム詳細)
  - [◇プレイヤーについて](#プレイヤーについて)
    - [①スケートボードの挙動](#スケートボードの挙動)
    - [②壁との衝突時](#壁との衝突時)
  - [◇UIについて](#uiについて)
    - [①インベントリー](#インベントリー)
    - [②ゲーム開始が「PressB」である理由](#ゲーム開始がpressbである理由)
  - [◇ミニマップについて](#ミニマップについて)
  - [◇お店とお客さんのUI表示/非表示を距離で切り替えている理由](#お店とお客さんのui表示非表示を距離で切り替えている理由)
  - [◇技術紹介](#技術紹介)
    - [①デプスシャドウ](#デプスシャドウ)
    - [②レールの処理](#レールの処理)

<br />


<section>
  <h2>作品概要</h2>
  <dl>
    <dt>タイトル</dt>
    <dd>Crazy Delivery(クレイジーデリバリー)</dd>
    <dt>制作人数</dt>
    <dd>1人</dd>
    <dt>制作期間</dt>
    <dd>2024年8月～2025年2月</dd>
    <dt>ゲームジャンル</dt>
    <dd>3Dアクションゲーム</dd>
    <dt>プレイ人数</dt>
    <dd>1人</dd>
    <dt>使用言語</dt>
    <dd>C++<br>HLSL</dd>
    <dt>使用ツール</dt>
    <dd>
      <ul>
        <li>Visual Studio 2022</li>
        <li>Visual Studio Code</li>
        <li>Adobe Photoshop 2025</li>
        <li>3ds Max 2024</li>
        <li>Effekseer</li>
        <li>GitHub</li>
        <li>Fork</li>
        <li>Trello</li>
      </ul>
    </dd>
    <dt>開発環境</dt>
    <dd>
      <ul>
        <li>学校内製の簡易エンジン</li>
        <li>Windows11</li>
      </ul>
    </dd>
  </dl>
</section>

<br />


# 担当ソースコード
<details><summary>
  ゲーム部分
  </summary>

* BackGround.cpp / .h
* Character.cpp / .h
* CustomerMan.cpp / .h
* CustomerMan_Hamburger.cpp / .h
* CustomerMan_Pizza.cpp / .h
* CustomerMan_Sushi.cpp / .h
* CustomerManFailureState.cpp / .h
* CustomerManHandState.cpp / .h
* CustomerManHappyState.cpp / .h
* CustomerManIdleState.cpp / .h
* CustomerWoman.cpp / .h
* DriftState.cpp / .h
* Fade.cpp / .h
* FocusLine.cpp / .h
* Game.cpp / .h
* GameCamera.cpp / .h
* GameEvents.cpp / .h
* GameInformation.cpp / .h
* GameSound.cpp / .h
* GameTimer.cpp / .h
* GameTitle.cpp / .h
* HasFoodManager.cpp / .h
* ICustomerManState.h
* IdleState.cpp / .h
* InventoryFoodIcon.cpp / .h
* InventoryRewardMoneyIcon.cpp / .h
* InventoryUI.cpp / .h
* IPlayerState.h
* IState.h
* JumpState.cpp / .h
* main.cpp
* MakeEffect.cpp / .h
* MapUI.cpp / .h
* ParameterManager.cpp / .h
* Path.cpp / .h
* PathStorage.cpp / .h
* Player.cpp / .h
* PlayerAngryState.cpp / .h
* PlayerDriftState.cpp / .h
* PlayerIdleState.cpp / .h
* PlayerJumpState.cpp / .h
* PlayerPushState.cpp / .h
* PlayerRunState.cpp / .h
* PlayerStartState.cpp / .h
* PushState.cpp / .h
* ResultUI.cpp / .h
* RunState.cpp / .h
* StartState.cpp / .h
* ShopBase.cpp / .h
* ShopHamburger.cpp / .h
* ShopPizza.cpp / .h
* ShopSushi.cpp / .h
* StartButtonUI.cpp / .h
* UIAnimationManager.cpp / .h
* UITypes.h
</details>

</details>

<details><summary>
   エンジン
   </summary>
  
  大文字は改造のみ
  * Bloom.cpp
  * Bloom.h
  * CameraCollisionSolver.cpp
  * CameraCollisionSolver.h
  * CollisionObject.cpp
  * CollisionObject.h
  * FontRender.cpp
  * FontRender.h
  * IRenderer.cpp
  * IRenderer.h
  * **k2EngineLow.cpp**
  * **k2EngineLow.h**
  * LevelRender.cpp
  * LevelRender.h
  * MapChipRender.cpp
  * MapChipRender.h
  * ModelRender.cpp
  * ModelRender.h
  * MyRenderer.cpp
  * MyRenderer.h
  * PointLight.cpp
  * PointLight.h
  * RenderingEngine.cpp
  * RenderingEngine.h
  * SceneLight.cpp
  * SceneLight.h
  * Shadow.cpp
  * Shadow.h
  * Shadowing.cpp
  * Shadowing.h
  * SkyCube.cpp
  * SkyCube.h
  * SpringCamera.cpp
  * SpringCamera.h
  * SpriteRender.cpp
  * SpriteRender.h

</details>

<details><summary>
   シェーダー
   </summary>
   
  * coolTime.fx
  * debugWireFrame.fx
  * gaussianBlur.fx
  * model.fx
  * postEffect.fx
  * drawShadowMap.fx
  * skyCube.fx
  * sprite.fx
 
</details>

# 操作説明
<img width="1920" height="1080" alt="InstructionCard" src="https://github.com/user-attachments/assets/e3a3e2db-71dd-4a56-ae97-815ef114b337" />


<br />

[⇧ 目次に戻る](#目次)

<a id="game-detail"></a>
# ゲーム説明
<br />

 ## ◇ゲーム詳細
> ### このゲームは、スケートボードで街を駆け巡るアクションゲームです。
> ### 制限時間内に、お店でテイクアウトした食べ物をお客さんに届けることが目的です。
> <img width="960" height="516" alt="image-3" src="https://github.com/user-attachments/assets/35f20fc3-b2ab-4489-885e-b0148a62bd47" />

> ### 食べ物の種類は、ハンバーガー、ピザ、寿司の3種類です。
> <img width="960" height="540" alt="image-4" src="https://github.com/user-attachments/assets/a7e399ff-614f-4801-a6c6-10d12192fce6" />

> ### お客さんに食べ物を届けると、報酬を稼ぐことが出来ます。
> <img width="960" height="517" alt="image-5" src="https://github.com/user-attachments/assets/e8cbb5aa-a538-4cc5-9f46-270766f6c6b6" />


<br />

[⇧ 目次に戻る](#目次)

<a id="player-detail"></a>

## ◇プレイヤーについて
<br />

<a id="player1"></a>

### ①スケートボードの挙動
> ## <b>・加速度<strong>
> ###  Bボタンを押すことでプレイヤーの進行方向に一定の加速度を加えます。
> ### プレイヤーが地面を蹴ったタイミングで加速するように調整しています。
>![accele3](https://github.com/user-attachments/assets/4063b457-fe73-46c8-bf79-cf7b32915900)

> ```ruby : PlayerRunState.cpp
>
> /// <summary>
> /// 加速度を設定
> /// </summary>
> /// <param name="accele">加速度</param>
> /// <param name="delayTime">加速度の適用を開始する遅延時間（単位：秒）</param>
> const void SetAccele(const Vector3& accele, const float& delayTime)
> {
>     this->m_acceleDelayTime = delayTime;
>     this->m_accele = accele;
>     // プレイヤーの速度を上限値以内に制限する
>     ApplySpeedLimit();
> }
>
> // Bボタン押されたら
> if (g_pad[0]->IsTrigger(enButtonB))
> {
>     const auto& forward = m_player->GetForward();
>     // 加速する
>     m_player->SetAccele(forward * PLAYER_ACCELE, m_acceleTime);
>     
>     return new PlayerPushState(m_player);
> }
> ```
<br />

[⇧ 目次に戻る](#目次)

> ## <b>・摩擦力<strong>
> ###  速度ベクトルの逆方向に作用し、速度を徐々に減少させ、最終的に停止する挙動を実現しています。
> ###  これにより、慣性を伴った自然な停止動作が可能です。
> ###  また、「Bボタン」の入力がない場合に速度が徐々に減速するような仕組みを取り入れました。
> ### ![friction2](https://github.com/user-attachments/assets/863cecbd-e37f-4970-8307-cc16ff78ef9d)<img width="480" height="270" alt="image-17" src="https://github.com/user-attachments/assets/7e876090-17f9-4889-81f2-8e5d24d1bf8f" />


>
> ## <実装の流れ>
>
> ```ruby : Player.cpp
> namespace
> {
>     // 定数の定義
>     const float DECELERATION_TIME = 5.0f;           // 減速にかかる時間（秒）
>     const float MIN_DECELERATION_FACTOR = 0.0f;     // 減衰係数の最小値
>     const float MAX_DOT_POWER = 0.9f;               // ドット積のべき乗の指数
>     const float MIN_FRICTION = 0.998f;              // 摩擦力の最小値
>     const float MAX_FRICTION = 1.0f;                // 摩擦力の最大値
> }
> 
> ```
>
> ### <b>手順１：フレームごとの経過時間を減速にかかる時間で割ります。<strong>
> ### その割合を１フレームから引くとこで、減衰係数を求まります。
>
> ```ruby : Player.cpp
>
>  // 減衰係数を計算（1フレームあたりに速度をどの割合で減らすか）
>  float decelerationFactor = 1.0f - (frameDeltaTime / DECELERATION_TIME);
>
> ```
>
> ### <b>手順２：現在のプレイヤーの速度ベクトルに減衰係数を乗算します。<strong>
> ### 摩擦力が働き、速度が徐々に減少していくように表現しています。
>
>```ruby : Player.cpp
>
>  // 速度ベクトルに減衰係数を適用して減速
>  m_velocity *= decelerationFactor;
>
> ```
>
> ### <b>手順３：スケートボードの進行方向と速度ベクトルの向きの関係によって、
> ### 摩擦力が変化するように調整しています。<strong>
>
>```ruby : Player.cpp
>
>  // ボードの方向と速度の方向で摩擦力を変化させる
>  // ボードが横を向いていたら摩擦力が強くなるようにする
>  auto velDir = m_velocity;
>  velDir.Normalize();
>
>  // ボードの前方向と速度ベクトルのドット積を計算
>  auto rictionAdjustment = pow(max(0.0f, velDir.Dot(m_forward)), MAX_DOT_POWER);
>
>  // 線形補間で減衰係数を調整（ボードが真横を向いている場合は摩擦力を増加）
>  decelerationFactor *= Math::Lerp(rictionAdjustment, MIN_FRICTION, MAX_FRICTION);
>
> ```
<br />

[⇧ 目次に戻る](#目次)

> ## <b>・ドリフト<strong>
> ###  RBボタンを押すことで、ドリフトが開始されます。
> ###  ドリフト中は、左スティックの入力方向に基づいてスムーズに回転します。
> ###  さらに、慣性の要素を加えることで、リアルなドリフト動作を再現しています。
> ![driftON (1) (2)](https://github.com/user-attachments/assets/c5690e43-3f00-4399-8c23-39a06fb882df)


<br />

[⇧ 目次に戻る](#目次)

<a id="player2"></a>

### ②壁との衝突時
> ###   もともと衝突時、加速を0にしていましたが
> ###   このゲームは疾走感があるゲームであるため、
> ###   ゲームを遊ぶテンポ感が落ちてしまいます。
> ###  ➡衝突時、反射するに加え、減速もしながら反射するように変更しました。
> ## ＜衝突時の比較＞
> ### ■反射の要素を追加していないもの。 
> ![reflectionOFF](https://github.com/user-attachments/assets/21a5a5aa-7d82-4419-a8df-bf68c8e305e2) 
> ### ■反射の要素を追加したもの。
>![reflectionON](https://github.com/user-attachments/assets/fcba1fb1-d791-433b-be49-7fe66fd87aec)


><img width="480" height="270" alt="image-3-1" src="https://github.com/user-attachments/assets/00711962-5433-435b-88f8-5f568a59d1bf" />

>
> ### <b>手順１：水平方向のみを考慮した衝突面の法線ベクトルを正規化します。<strong>
>
> ```ruby : Player.cpp
>
>  //衝突法線ベクトル
>  Vector3 normalXZ = callback.normal;
>  //水平方向のみを考慮
>  normalXZ.y = NORMAL_Y_VALUE;
>  normalXZ.Normalize();
>
> ```
>
> ### <b>手順２：速度ベクトルと、先ほどの法線ベクトルの内積を求めます。<strong>
>
>```ruby : Player.cpp
>
>  m_velocity.Dot(normalXZ);
>
> ```
>
> ### <b>手順３：内積の値に、反射のスカラー値を乗算します。<strong>
> ### 乗算することで反射の強さを調整できます。
>
>```ruby : Player.cpp
>
> m_velocity.Dot(normalXZ * REFLECTION_SCALAR);
>
> ```
>
> ### <b>手順４：先ほど求めた、法線ベクトルに反射の強さを乗算します。<strong>
> ### 乗算することで、反射方向のベクトル、つまり衝突後の進行方向が求まります。
> ```ruby : Player.cpp
> // 反射ベクトルを計算
> m_reflection = normalXZ * m_velocity.Dot(normalXZ * REFLECTION_SCALAR);
>
> ```
>
> ### <b>手順５：元の速度ベクトルに手順３で求めた衝突後の進行方向を加算します。<strong>
> ### 加算することで、壁にぶつかって反射したような動きを実装しました。
>  ```ruby : Player.cpp
>  //反射ベクトルを加算して新しい方向を決定
>  m_reflection += m_velocity;
> ```
<br />

[⇧ 目次に戻る](#目次)

<a id="ui-detail"></a>

## ◇UIについて

<a id="ui1"></a>

### ①インベントリー
> ### 食べ物を取得した時に、食べ物のUIに動きを出して
> ### 画面右上にあるインベントリーにスライドさせました。
> ![slideOFF](https://github.com/user-attachments/assets/c818db57-722b-4588-ae37-82691c514503)![slideON](https://github.com/user-attachments/assets/7246706b-c6e0-4d9b-9c68-4183d004eb5b)

> ### ➡動きを付けることで、取得する度に現在のインベントリーの状態が確認できます。
> ###   また、動きを付ける前は取得した効果音と、
> ###   グレー表示（持っていない）から色付き表示(持っている)の切り替えのみでしたが
> ###   取得した感を上げるために動きを付けました。

<br />

[⇧ 目次に戻る](#目次)

<a id="ui2"></a>

### ②ゲーム開始が「PressB」である理由
> ### 「Bボタン」を押して、ゲームを開始させることで
> ### スケートボードの加速するボタンが「Bボタン」であることを
> ### 遊ぶユーザーにスムーズに教えるためです。
>![PressB](https://github.com/user-attachments/assets/b103339b-811c-40eb-96b1-b3583cbfdca6)


<br />

[⇧ 目次に戻る](#目次)

<a id="map"></a>

## ◇ミニマップについて
> ### プレイヤー、お客さん、お店はミニマップの「円形の範囲外」に出ると非表示になります。
> ### ミニマップで表示する範囲を「円形の範囲」として定義し、
> ### カメラやプレイヤーの位置に基づき、座標を変換します。
> ### また、ワールド座標系をミニマップ上のスクリーン座標系に変換します。
>![map](https://github.com/user-attachments/assets/4203aed5-05e6-4eeb-a1ce-9c7d090ab8a6)


<br />

[⇧ 目次に戻る](#目次)

<a id="shop-ui"></a>

## ◇お店とお客さんのUI表示/非表示を距離で切り替えている理由
> ### 視覚的な情報過多を防ぎ、ゲームプレイを集中しやすくしています。
> ### 各お店やお客さんの座標とプレイヤーの座標をベクトルで取得し、その差分を計算します。
> ### 計算された距離が一定値以内であれば、該当するUIを表示します。
> ### また、一定値を超えた場合はUIを非表示にします。
> ### カメラの前方ベクトルとショップやお客さんへの方向ベクトルの内積を用いて、視野角内にあるかを計算します。
> ### これにより、プレイヤーから見える範囲内にある場合のみUIが表示されるようにしています。
>![shopUI](https://github.com/user-attachments/assets/de27e8e2-7557-44e2-aaa3-1fd418f69af1)  ![customerUI](https://github.com/user-attachments/assets/05184e3c-b51f-40e5-b98b-62c0c1b85c95)


<br />

[⇧ 目次に戻る](#目次)

<a id="tech-detail"></a>

## ◇技術紹介

<br />

<a id="tech1"></a>

### ①デプスシャドウ
> ### デプスシャドウは「影はライトの光が遮られている場所に落ちるはずなので、
> ### 影が落ちる箇所には、手前に遮蔽物があるはず」という考え方をもとに影を落としています。
> ### そして、投影シャドウのデメリットである「影が落ちないはずの場所に影が落ちてしまう」と「セルフシャドウが行えない」という問題を解決できます。
>
> ## <実装の流れ>
> ### <b>手順１：Z値を書き込んだレンダリングターゲットを作成します。<strong>
><img width="1094" height="676" alt="depthShadow" src="https://github.com/user-attachments/assets/108c6946-006f-4e25-9f2b-46663d1d49af" />

> 
> 
> ### <b>手順２：ライトビュースクリーン空間でのＺ値を計算します。<strong>
>
> ```
>  //ライトビュースクリーン空間でのＺ値を計算する
>  float zInLVP = psIn.posInLVP.z / psIn.posInLVP.w;
> ```
>
> ### <b>手順３：シャドウマップに書き込まれているＺ値を比較し、隠蔽されていたら影を落とします。<strong>
>
> ```
>  //UV座標を使ってシャドウマップから影情報をサンプリング
> float3 shadowMap = 1.0f;
> 
> if (shadowMapUV.x > 0.0f && shadowMapUV.x < 1.0f 
>     && shadowMapUV.y > 0.0f && shadowMapUV.y < 1.0f)
> {
>
>     //シャドウマップに書き込まれているZ値と比較
>     //計算したUV座標を使って、シャドウマップから深度値をサンプリング
>     float zInShadowMap = g_shadowMap.Sample(g_sampler, shadowMapUV).r;
>
>     //モデルの深度値（シャドウマップの深度値）とステージの深度値を比べて
>     //ステージの深度値がモデルの深度値よりも大きかったら影を落とす
>     if (zInLVP > zInShadowMap)
>     {
>         //隠蔽されている
>         shadowAttn *= 0.5f; 
>     }
> }
> 
> return shadowAttn;
> ```

 <br />

[⇧ 目次に戻る](#目次)

<a id="tech2"></a>

 ### ②レールの処理
> ![rail](https://github.com/user-attachments/assets/c0c3056d-a4df-4992-84a6-ac62577e8d9f)

> ## ＜実装の流れ＞
> ### <b>手順１：レールの各ポイントを管理するPathクラスを作成します。<strong>
> ### ＊ポイントリストをソートしているため、誤って、パスの配置が乱雑になることなく、順番通りに設定しています。
>
> ```
>void Path::Build()
>{
>	// ポイントリストをソートする(昇順)
>	std::sort(m_pointList.begin(), m_pointList.end(), [](Point const& lhs, Point const& rhs)
>	{
>		return lhs.no < rhs.no;
>	});
> }
>
>```
>
> ### <b>手順２：すべてのPathインスタンスを管理する PathStorageクラス を作成します。<strong>
> ### ここではシングルトンパターンで作成しています。
> ### （シングルトンパターンを使用している理由）
> ### オブジェクトの実体化を１度だけにとどめているので、何度も実体化するものと比べてパフォーマンス面での効率が良くなるためです。
>
> ### <b>手順３：レールをゲームオブジェクトとしてロードできたら、プレイヤーがレールに沿って移動する処理を作成します。<strong>
> <img width="1280" height="720" alt="rail" src="https://github.com/user-attachments/assets/ac63d01c-1762-45d4-9139-15e6696343ec" />

> ### ＜プレイヤーがレールの上に乗ることができる条件＞
> ### プレイヤーの座標とレール内にあるパス移動する順番の
> ### １番目との距離が一定以内になると、１番目から順にパス移動が開始されます。
>
> ### <b>手順４：内積を使ってレール移動が開始される範囲を制御します。<strong>
> ### プレイヤーの前方向ベクトルと、レールの進行方向との内積を計算します。
> 
> ```
>void Player::CheckCollisionWithSlope()
>{
> //パスの前方向ベクトルを計算
> Vector3 pathForwardVec = points[1].position - points[0].position;
> pathForwardVec.Normalize();
>
> m_forwardDotPath = m_forward.Dot(pathForwardVec);
> }
>
>```
>
> ### 内積の値が<b>「m_forwardDotPath >= 0」(正の数)<strong>である場合、
> ### プレイヤーがレールの進行方向に近い方向を向いているため、レールに乗る処理を行います。
> ### もし、内積の値が<b>「m_forwardDotPath < 0」(負の数)<strong>ならば、
> ### プレイヤーがレールの逆方向を向いているため、レールに乗らないように設定しています。
 <br />

[⇧ 目次に戻る](#目次)

