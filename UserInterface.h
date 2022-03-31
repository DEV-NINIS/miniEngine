#ifndef DEF_USER_INTERFACE
#define DEF_USER_INTERFACE

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glmAnimation3D.h"

class UserInterface 
{
public:
	// 2 constructors
	UserInterface(GLFWwindow* window);
	UserInterface(GLFWwindow* window, int randomBumberJustForSurcharge);
	UserInterface(GLFWwindow* window, float LastedFrameColorRFile, float LastedFrameColorGFile,
		float LastedFrameColorBFile, float LastedFloatFrameXFile, float LastedFloatFrameYFile, float LastedFloatFrameZFile,
		float LastedRotateXValueFile, float LastedRotateYValueFile, float LastedRotateZValueFile, float LastedColorObjectRFile,
		float LastedColorObjectGFile, float LastedColorObjectBFile, float LastedPositionObjectXFile, float LastedPositionObjectYFile,
		float LastedPositionObjectZFile, float CameraSpeedFile, const char* filePathPointerFile);

	virtual ~UserInterface();
	void setStyleSettingFrame(GLFWwindow* window);
	bool inputDemandingChangeFOV() const;
	bool inputDemandSelectFolderForTex1() const;
	bool inputDemandSelectFolderForTex2() const;
	bool confirmFilePath() const;
	void inputFileTexture1(char* filePathTex1);
	void inputFileTexture2(char* filePathTex2);
	void interfaceEditorWindow();
	float setRotateAroundXValue();
	float setRotateAroundYValue();
	float setRotateAroundZValue();
	float setScaleCube();
	float setScaleCubeX();
	float setScaleCubeZ();
	void setPercentTexture();
	void setCameraSpeed();
	void setColorR();
	void setColorG();
	void setColorB();
	void setColorObjectR();
	void setColorObjectG();
	void setColorObjectB();
	void setPositionObjectX();
	void setPositionObjectY();
	void setPositionObjectZ();
	void setChangeFOV();
	// getting value rotate
	float getpercentTexture() const;
	int getIndicatorTextureFilePath();
	float& getValueRotateX();
	float& getValueRotateY();
	float& getValueRotateZ();
	float getFOV_Value() const;
	// 
	// getting value Position
	float getPositionObjectX() const;
	float getPositionObjectY() const;
	float getPositionObjectZ() const;
	// value camera
	float getCmerraSpeed() const;
	// getting values for scale 
	float getScaleCubeX() const;
	float getScaleCubeY() const;
	float getScaleCubeZ() const;

	void setColorEditorFrame(int objectOrFrame);
	void setColorEditorObject(int objectOrFrame);

	// node window 
	void setNodeWindow();
	void addNode();

	// node editor
	void setStyleNodeFrame();
	void setNodeInformation(); // this fonction initialise the fps latence .ect

	void setNodeRotateMeshWithRadius();

	// gettting values for save
	void setSettingFrame();
	bool inputDemandingChangeColorFrame();
	bool ButtonForSetAnimation();
	bool changeColorFrame();
	void setLastedmatrix();
	void endFrame();
	float LastedFloatFrame;
	float LastedFloatFrameX;
	float LastedFloatFrameY;
	float LastedFloatFrameZ;
	std::vector<char*> filePathPointer;
	static char filePath1[150];
	static char filePath2[150];
	static char filePath3[150];
	static char filePath4[150];
	static char filePath5[150];
	static const char* filepath1ConstChar;
	static const char* filepath2ConstChar;
	static float LastedColorObject[2];
	static float lastedColorFrame[2];

	protected:
		int lastedFilePath;
		float* size1 = nullptr;
		float FOV;
		float LastedRotateXValue;
		float LastedRotateYValue;
		float LastedRotateZValue;
		
		float LastedPositionObjectX;
		float LastedPositionObjectY;
		float LastedPositionObjectZ;
		float percentTexture;
		float CameraSpeed;
};

#endif // !1

