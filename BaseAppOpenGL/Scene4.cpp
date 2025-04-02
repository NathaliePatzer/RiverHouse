#include "Scene4.h"

CScene4::CScene4()
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
	//pTextures = new CTexture();	

	fZ = -5.0f;
	up = true;

}


CScene4::~CScene4(void)
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




int CScene4::DrawGLScene(void)	// Função que desenha a cena
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
	//Draw3DSGrid(20.0f, 20.0f);

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
	
	//Chão
	glBegin(GL_QUADS);
	glColor3ub(153, 189, 199);
	glVertex3f(-30.0f, 0.0f, 30.0f);
	glVertex3f(30.0f, 0.0f, 30.0f);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glVertex3f(-30.0f, 0.0f, -30.0f);
	glEnd();

	//Boneco de neve 
	glPushMatrix();
		//esfera maior
		glTranslatef(-2.0f, 1.8f, 0.0);
		glRotatef(fZ, 0.0f, 0.0f, 1.0f);
		glColor3ub(218, 229, 232);
		auxSolidSphere(2.0);
			
			//esfera média
			glPushMatrix();
			glTranslatef(0.0f, 2.5f, 0.0f);
			glColor3ub(218, 229, 232);
			auxSolidSphere(1.5);
			glPopMatrix();

			//cabeça
			glPushMatrix();
			glTranslatef(0.0f, 4.6f, 0.0f);
			glColor3ub(218, 229, 232);
			auxSolidSphere(1.0);
			glPopMatrix();

			//botões
			glPushMatrix();
			glTranslatef(0.0f, 2.8f, 1.5f);
			glColor3ub(191, 40, 40);
			auxSolidSphere(0.2);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.0f, 2.2f, 1.5f);
			glColor3ub(191, 40, 40);
			auxSolidSphere(0.2);
			glPopMatrix();

			//olhos
			glPushMatrix();
			glTranslatef(-0.5f, 4.6f, 1.0f);
			glColor3ub(18, 17, 17);
			auxSolidSphere(0.2);
			glPopMatrix();

			glPushMatrix();
			glTranslatef(0.5f, 4.6f, 1.0f);
			glColor3ub(18, 17, 17);
			auxSolidSphere(0.2);
			glPopMatrix();

			//nariz
			glPushMatrix();
			glTranslatef(0.0f, 4.2f, 0.8f);
			glColor3ub(184, 105, 37);
			auxSolidCone(0.2, 0.6);
			glPopMatrix();

			//base chapéu
			glPushMatrix();
			glTranslatef(0.0f, 4.7f, 0.0f);
			glColor3ub(67, 71, 196);
			auxSolidCylinder(1.0f, 0.4f);
			glPopMatrix();

			//corpo chapéu
			glPushMatrix();
			glTranslatef(0.0f, 5.5f, 0.0f);
			glColor3ub(67, 71, 196);
			auxSolidCylinder(0.8f, 1.2f);
			glPopMatrix();

	glPopMatrix();



	//movimenta o boneco 
	if (fZ > 45.0f)
		up = false;
	else if (fZ <= -45.0f)
		up = true;

	if (up)
		fZ += 0.5f;
	else
		fZ -= 0.5f;

	for (int i = -50; i < 50; i += 5) {
		for (int j = -50; j < 50; j += 10) {
			DrawTree(i, 0.0f, j);
		}
		
	}

	





	



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




void CScene4::MouseMove(void) // Tratamento de movimento do mouse
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

void CScene4::KeyPressed(void) // Tratamento de teclas pressionadas
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

void CScene4::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
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
void CScene4::Draw3DSGrid(float width, float length)
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



void CScene4::DrawAxis()
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

void CScene4::DrawTree(float x, float y, float z) {
	// Copa da árvore
	glPushMatrix();
	glTranslatef(x, y, z);

	glPushMatrix();
	glTranslatef(0.0f, 4.5f, 10.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(39, 130, 69);
	auxSolidCone(2.0, 6.0);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 10.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(33, 110, 58);
	auxSolidCone(2.0, 6.0);
	glPopMatrix();

	// Tronco da árvore
	glPushMatrix();
	glTranslatef(0.0f, 2.0f, 10.0f);
	glColor3ub(110, 98, 70);
	auxSolidCylinder(0.5, 3.0);
	glPopMatrix();

	glPopMatrix();
}
