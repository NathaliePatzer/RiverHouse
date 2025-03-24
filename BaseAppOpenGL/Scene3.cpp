#include "Scene3.h"

CScene3::CScene3()
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
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.1f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	//pTextures = new CTexture();	



	x = 5.0f;
	y = 0.0f;
	z = 0.0f;
	speed = 0.1f;
	angle = 0.0f;

	fY = -5.0f;
	bUp = true;
}


CScene3::~CScene3(void)
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




int CScene3::DrawGLScene(void)	// Função que desenha a cena
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


	// Arvore 1 - pinheiro
	// Copa da árvore
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

	// Arvore 2 - rosa
	// Copa da árvore
	glPushMatrix();
	glTranslatef(-10.0f, 5.0f, 6.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(209, 125, 194);
	auxSolidIcosahedron(2.5);
	glPopMatrix();

	// Tronco da árvore
	glPushMatrix();
	glTranslatef(-10.0f, 2.0f, 6.0f);
	glColor3ub(110, 98, 70);
	auxSolidCylinder(0.5, 3.0);
	glPopMatrix();

	// Arvore 3 - laranja
	// Copa da árvore
	glPushMatrix();
	glTranslatef(-5.0f, 5.0f, 2.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(191, 140, 82);
	auxSolidDodecahedron(2.5);
	glPopMatrix();

	// Tronco da árvore
	glPushMatrix();
	glTranslatef(-5.0f, 2.0f, 2.0f);
	glColor3ub(110, 98, 70);
	auxSolidCylinder(0.5, 3.0);
	glPopMatrix();

	// Arvore 4 - verde escuro
	// Copa da árvore
	glPushMatrix();
	glTranslatef(-10.0f, 5.0f, -10.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(40, 84, 33);
	auxSolidIcosahedron(2.5);
	glPopMatrix();

	// Tronco da árvore
	glPushMatrix();
	glTranslatef(-10.0f, 2.0f, -10.0f);
	glColor3ub(110, 98, 70);
	auxSolidCylinder(0.5, 3.0);
	glPopMatrix();

	// Arvore 5 - pinheiro 2
	// Copa da árvore
	glPushMatrix();
	glTranslatef(-2.0f, 3.0f, -10.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(33, 110, 58);
	auxSolidCone(2.0, 6.0);;
	glPopMatrix();

	// Tronco da árvore
	glPushMatrix();
	glTranslatef(-2.0f, 2.0f, -10.0f);
	glColor3ub(110, 98, 70);
	auxSolidCylinder(0.5, 3.0);
	glPopMatrix();

	//Arbusto 1
	glPushMatrix();
	glTranslatef(8.0f, 0.5f, -10.0f);
	glRotatef(10.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(93, 138, 85);
	auxSolidDodecahedron(1.5);
	glPopMatrix();

	//Arbusto 2
	glPushMatrix();
	glTranslatef(10.0f, 0.5f, 0.0f);
	glRotatef(40.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(72, 135, 61);
	auxSolidDodecahedron(1.5);
	glPopMatrix();

	//Arbusto 3
	glPushMatrix();
	glTranslatef(8.0f, 0.5f, 10.0f);
	glRotatef(85.0f, 1.0f, 0.0f, 0.0f);
	glColor3ub(70, 173, 52);
	auxSolidDodecahedron(1.5);
	glPopMatrix();

	// Casa
	glPushMatrix();
	glTranslatef(0.0f, 1.5f, 0.0f);
	glColor3ub(77, 95, 184);
	auxSolidBox(4, 3, 6);
	glPopMatrix();

	//Aba 1 Casa
	glBegin(GL_TRIANGLES);
	glColor3ub(163, 132, 88);
	glVertex3f(-2.0f, 3.0f, 3.0f);
	glVertex3f(2.0f, 3.0f, 3.0f);
	glVertex3f(0.0f, 6.0f, 3.0f);
	glEnd();

	//Aba 2 Casa
	glBegin(GL_TRIANGLES);
	glColor3ub(235, 190, 127);
	glVertex3f(-2.0f, 3.0f, -3.0f);
	glVertex3f(0.0f, 6.0f, -3.0f);
	glVertex3f(2.0f, 3.0f, -3.0f);
	glEnd();

	//Telhado esquerdo
	glBegin(GL_QUADS);
	glColor3ub(204, 165, 110);
	glVertex3f(-2.0f, 3.0f, -3.0f);
	glVertex3f(-2.0f, 3.0f, 3.0f);
	glVertex3f(0.0f, 6.0f, 3.0f);
	glVertex3f(0.0f, 6.0f, -3.0f);
	glEnd();

	//Telhado direito
	glBegin(GL_QUADS);
	glColor3ub(204, 165, 110);
	glVertex3f(2.0f, 3.0f, -3.0f);
	glVertex3f(0.0f, 6.0f, -3.0f);
	glVertex3f(0.0f, 6.0f, 3.0f);
	glVertex3f(2.0f, 3.0f, 3.0f);
	glEnd();

	//Chão
	glBegin(GL_QUADS);
	glColor3ub(77, 184, 93);
	glVertex3f(2.0f, 0.0f, -30.0f);
	glVertex3f(-30.0f, 0.0f, -30.0f);
	glVertex3f(-30.0f, 0.0f, 30.0f);
	glVertex3f(2.0f, 0.0f, 30.0f);
	glEnd();

	//Rio
	glBegin(GL_QUADS);
	glColor3ub(109, 207, 242);
	glVertex3f(2.0f, 0.0f, 30.0f);
	glVertex3f(6.0f, 0.0f, 30.0f);
	glVertex3f(6.0f, 0.0f, -30.0f);
	glVertex3f(2.0f, 0.0f, -30.0f);
	glEnd();

	//Chão 2
	glBegin(GL_QUADS);
	glColor3ub(77, 184, 93);
	glVertex3f(6.0f, 0.0f, 30.0f);
	glVertex3f(30.0f, 0.0f, 30.0f);
	glVertex3f(30.0f, 0.0f, -30.0f);
	glVertex3f(6.0f, 0.0f, -30.0f);
	glEnd();

	//Lua
	glPushMatrix();
	glTranslatef(-2.0f, 20.0f, -8.0f);
	glColor3ub(147, 211, 217);
	auxSolidSphere(1.0);
	glPopMatrix();

	//Roda d'agua
	glPushMatrix();
	glTranslatef(2.5f, 1.5f, 0.0f);
	glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
	glColor3ub(89, 80, 67);
	auxSolidTorus(0.5, 1.5);
	glPopMatrix();




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




void CScene3::MouseMove(void) // Tratamento de movimento do mouse
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

void CScene3::KeyPressed(void) // Tratamento de teclas pressionadas
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

	if (GetKeyState(VK_LEFT) & 0x80)
	{
		x -= speed;
	}
	if (GetKeyState(VK_RIGHT) & 0x80)
	{
		x += speed;
	}
	if (GetKeyState(VK_UP) & 0x80)
	{
		z -= speed;
	}
	if (GetKeyState(VK_DOWN) & 0x80)
	{
		z += speed;
	}
	if (GetKeyState(VK_PRIOR) & 0x80)
	{
		y += speed;
	}
	if (GetKeyState(VK_NEXT) & 0x80)
	{
		y -= speed;
	}


}

void CScene3::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
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
void CScene3::Draw3DSGrid(float width, float length)
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



void CScene3::DrawAxis()
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


void CScene3::DrawTriangle()
{
	glBegin(GL_TRIANGLES);
	glColor3ub(255, 0, 0);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	glColor3ub(0, 255, 0);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	glColor3ub(0, 0, 255);
	glVertex3f(1.0f, 0.0f, 1.0f);
	glVertex3f(1.0f, 0.0f, -1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);

	glColor3ub(38, 153, 113);
	glVertex3f(-1.0f, 0.0f, -1.0f);
	glVertex3f(-1.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 2.0f, 0.0f);
	glEnd();
}


void CScene3::DrawCube()
{
	glBegin(GL_QUADS);
	// Frente
	glColor3ub(255, 0, 0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f, -1.0f, 1.0f);
	glVertex3f( 1.0f,  1.0f, 1.0f);
	glVertex3f(-1.0f,  1.0f, 1.0f);

	// Direita
	glColor3ub(0, 255, 0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);

	// Trás
	glColor3ub(0, 0, 255);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);

	// Esquerda
	glColor3ub(255, 0, 255);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(-1.0f, -1.0f,  1.0f);
	glVertex3f(-1.0f, 1.0f,  1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// Topo
	glColor3ub(255, 255, 0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	glVertex3f( 1.0f, 1.0f, 1.0f);
	glVertex3f( 1.0f, 1.0f, -1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	// Base
	glColor3ub(0, 255, 255);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	glEnd();
}