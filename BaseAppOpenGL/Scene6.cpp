#include "Scene6.h"

CScene6::CScene6()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;
	
	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.2f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	pTextures = new CTexture();
	pTextures->CreateTextureAnisotropic(0, "../Scene6/CRATE.BMP");
	pTextures->CreateTextureAnisotropic(1, "../Scene6/grama.bmp");
	pTextures->CreateTextureAnisotropic(2, "../Scene6/parede.bmp");
	pTextures->CreateTextureAnisotropic(3, "../Scene6/paredejanela.bmp");
	pTextures->CreateTextureAnisotropic(4, "../Scene6/paredeporta.bmp");
	pTextures->CreateTextureAnisotropic(5, "../Scene6/R1.jpg");
}


CScene6::~CScene6(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}	
}




int CScene6::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter
	
	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	// Habilita mapeamento de texturas
	glEnable(GL_TEXTURE_2D);

	// Carrega a textura 
	pTextures->ApplyTexture(1);

	//CHÃO
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-30.0f, 0.0f, 30.0f);
	glTexCoord2d(5.0f, 0.0f); glVertex3f(30.0f, 0.0f, 30.0f);
	glTexCoord2d(5.0f, 5.0f); glVertex3f(30.0f, 0.0f, -30.0f);
	glTexCoord2d(0.0f, 5.0f); glVertex3f(-30.0f, 0.0f, -30.0f);
	glEnd();

	//CASA

	//Parede janela
	pTextures->ApplyTexture(3);

	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Parede porta
	pTextures->ApplyTexture(4);

	glPushMatrix();
	glTranslatef(4.0f, 2.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Parede Lisa
	pTextures->ApplyTexture(2);

	glPushMatrix();
	glTranslatef(8.0f, 2.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Parede janela frente
	pTextures->ApplyTexture(3);

	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Parede janela trás
	pTextures->ApplyTexture(3);

	glPushMatrix();
	glTranslatef(0.0f, 2.0f, -4.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Parede porta trás
	pTextures->ApplyTexture(4);

	glPushMatrix();
	glTranslatef(4.0f, 2.0f, -4.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Parede Lisa trás
	pTextures->ApplyTexture(2);

	glPushMatrix();
	glTranslatef(8.0f, 2.0f, -4.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Parede janela frente trás
	pTextures->ApplyTexture(3);

	glPushMatrix();
	glTranslatef(12.0f, 2.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-2.0f, 2.0f, -2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//TELHADO
	//Telhado frente

	pTextures->ApplyTexture(5);

	glPushMatrix();
	glTranslatef(4.0f, 6.0f, 0.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-7.0f, -2.0f, 2.0f);
	glTexCoord2d(2.0f, 0.0f); glVertex3f(7.0f, -2.0f, 2.0f);
	glTexCoord2d(2.0f, 2.0f); glVertex3f(7.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 2.0f); glVertex3f(-7.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Telhado trás

	pTextures->ApplyTexture(5);

	glPushMatrix();
	glTranslatef(4.0f, 6.0f, 0.0f);
	glRotatef(180.0f, 0, 1, 0);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-7.0f, -2.0f, 2.0f);
	glTexCoord2d(2.0f, 0.0f); glVertex3f(7.0f, -2.0f, 2.0f);
	glTexCoord2d(2.0f, 2.0f); glVertex3f(7.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 2.0f); glVertex3f(-7.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//ABA CASA

	//Frente
	pTextures->ApplyTexture(2);

	glPushMatrix();
	glTranslatef(0.0f, 6.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(0.5f, 1.0f); glVertex3f(-2.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Trás
	pTextures->ApplyTexture(2);

	glPushMatrix();
	glTranslatef(12.0f, 6.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.0f, -2.0f, -2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.0f, -2.0f, 2.0f);
	glTexCoord2d(0.5f, 1.0f); glVertex3f(-2.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//CAIXAS

	//Grande
	
	//Esquerda
	pTextures->ApplyTexture(0);

	glPushMatrix();
	glTranslatef(12.0f, 2.0f, 4.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Direita
	glPushMatrix();
	glTranslatef(12.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 2.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Frente
	glPushMatrix();
	glTranslatef(12.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Trás
	glPushMatrix();
	glTranslatef(14.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f, 2.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 2.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Cima
	glPushMatrix();
	glTranslatef(12.0f, 4.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Pequena baixo

	//Esquerda
	pTextures->ApplyTexture(0);

	glPushMatrix();
	glTranslatef(10.0f, 2.0f, 4.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Direita
	glPushMatrix();
	glTranslatef(10.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Frente
	glPushMatrix();
	glTranslatef(10.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Trás
	glPushMatrix();
	glTranslatef(12.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Cima
	glPushMatrix();
	glTranslatef(10.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Pequena cima

	glPushMatrix();

	// 1. Move o centro para a origem
	glTranslatef(11.0f, 4.0f, 7.0f);

	// 2. Rotaciona 45 graus no eixo X
	glRotatef(-45.0f, 0.0f, 1.0f, 0.0f);

	// 3. Move de volta
	glTranslatef(-11.0f, -4.0f, -7.0f);

	//Esquerda
	pTextures->ApplyTexture(0);

	glPushMatrix();
	glTranslatef(10.0f, 4.0f, 4.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Direita
	glPushMatrix();
	glTranslatef(10.0f, 4.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glEnd();
	glPopMatrix();

	//Frente
	glPushMatrix();
	glTranslatef(10.0f, 4.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Trás
	glPushMatrix();
	glTranslatef(12.0f, 4.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, -2.0f, 0.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.0f, -2.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Cima
	glPushMatrix();
	glTranslatef(10.0f, 4.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();

	//Baixo 
	glPushMatrix();
	glTranslatef(10.0f, 2.0f, 6.0f);
	glBegin(GL_QUADS);
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.0f, 0.0f, 2.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.0f, 0.0f, 0.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);
	glEnd();
	glPopMatrix();
	
	glPopMatrix();

	// Desabilita mapeamento de texturas
	glDisable(GL_TEXTURE_2D);



	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 100, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime()/1000));


	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene6::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene6::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}



}

void CScene6::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene6::Draw3DSGrid(float width, float length)
{

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor3f(0.0f, 0.3f, 0.0f);
	glPushMatrix();
	for (float i = -width; i <= length; i += 1)
	{
		for (float j = -width; j <= length; j += 1)
		{
			// inicia o desenho das linhas
			glBegin(GL_QUADS);
			glNormal3f(0.0f, 1.0f, 0.0f);
			glTexCoord2f(0.0f, 0.0f); glVertex3f(i, 0.0f, j + 1);
			glTexCoord2f(1.0f, 0.0f); glVertex3f(i + 1, 0.0f, j + 1);
			glTexCoord2f(1.0f, 1.0f); glVertex3f(i + 1, 0.0f, j);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(i, 0.0f, j);
			glEnd();
		}
	}
	glPopMatrix();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}



void CScene6::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


