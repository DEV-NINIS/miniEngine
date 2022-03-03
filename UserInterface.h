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
	UserInterface(GLFWwindow* window, float LastedFrameColorRFile, float LastedFrameColorGFile,
		float LastedFrameColorBFile, float LastedFloatFrameXFile, float LastedFloatFrameYFile, float LastedFloatFrameZFile,
		float LastedRotateXValueFile, float LastedRotateYValueFile, float LastedRotateZValueFile, float LastedColorObjectRFile,
		float LastedColorObjectGFile, float LastedColorObjectBFile, float LastedPositionObjectXFile, float LastedPositionObjectYFile,
		float LastedPositionObjectZFile, float CameraSpeedFile, const char* filePathPointerFile);

	virtual ~UserInterface();
	bool inputColorR() const;
	bool inputColorG() const;
	bool inputColorB() const;
	bool inputColorA() const;
	bool inputDemandingScaleCube() const;
	bool inputDemandingScaleCubeX() const;
	bool inputDemandingScaleCubeY() const;
	bool inputDemandingScaleCubeZ() const;
	bool inputDemandingPositionObject() const;
	bool inputDemandingPositionObjectX() const;
	bool inputDemandingPositionObjectY() const;
	bool inputDemandingPositionObjectZ() const;
	bool inputDemandCameraSpeed() const;
	bool inputDemandingCamera() const;
	bool inputDemandingAnimation() const;
	bool inputDemandingRotate() const;
	bool inputDemandingChangeColorObject() const;
	bool inputDemandingTexture1() const;
	bool inputDemandingRotateAroundX() const;
	bool inputDemandingRotateAroundY() const;
	bool inputDemandingRotateAroundZ() const;
	bool inputDemandingRotateRight() const;
	bool inputDemandingRotateLeft() const;
	bool inputDemandingChangeFOV() const;
	bool inputDemandSelectFolderForTex1() const;
	bool inputDemandSelectFolderForTex2() const;
	bool confirmFilePath() const;
	void inputFileTexture1(char* filePathTex1);
	void inputFileTexture2(char* filePathTex2);
	void interfacebeginCanvas();
	float setRotateAroundXValue();
	float setRotateAroundYValue();
	float setRotateAroundZValue();
	float setScaleCube();
	float setScaleCubeX();
	float setScaleCubeY();
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
	// getting value color
	float getColorR() const;
	float getColorG() const;
	float getColorB() const;
	float getColorObjectR() const;
	float getColorObjectG() const;
	float getColorObjectB() const;
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

	protected:
		int lastedFilePath;
		float* size1 = nullptr;
		float FOV;
		float LastedFrameColorR;
		float LastedFrameColorG;
		float LastedFrameColorB;
		float LastedRotateXValue;
		float LastedRotateYValue;
		float LastedRotateZValue;
		float LastedColorObjectR;
		float LastedColorObjectG;
		float LastedColorObjectB;
		float LastedPositionObjectX;
		float LastedPositionObjectY;
		float LastedPositionObjectZ;
		float percentTexture;
		float CameraSpeed;
};

#endif // !1

