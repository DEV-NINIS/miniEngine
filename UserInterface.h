#ifndef DEF_USER_INTERFACE
#define DEF_USER_INTERFACE

#include <iostream>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "glmAnimation3D.h"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "imgui/imgui_node_editor.h"
#include "imgui/imgui_node_editor_internal.h"



	static int ADD_NODE_ROTATE_RIGHT_variable = NULL;
	static int ADD_NODE_ROTATE_LEFT_variable = NULL;
	static int ADD_NODE_MOVE_CAMERA_LEFT_variable = NULL;
	static int ADD_NODE_MOVE_CAMERA_RIGHT_variable = NULL;
	static int ADD_NODE_MOVE_CAMERA_UP_variable = NULL;
	static int ADD_NODE_MOVE_CAMERA_DOWN_variable = NULL;
	static int ADD_NODE_ROTATE_AROUD_X_MATRIX_variable = NULL;
	static int ADD_NODE_ROTATE_AROUND_Y_MATRIX_variable = NULL;
	static int ADD_NODE_ROTATE_AROUND_Z_MATRIX_variable = NULL;
	static int ADD_NODE_CHANGE_CAMERA_SPEED_variable = NULL;
	static int ADD_NODE_CHANGE_PERCENT_TEXTURE_variable = NULL;
	static int ADD_NODE_CHANGE_POSITION_X_variable = NULL;
	static int ADD_NODE_CHANGE_POSITION_Y_variable = NULL;
	static int ADD_NODE_CHANGE_POSITION_Z_variable = NULL;
	static int ADD_NODE_CHANGE_COLOR_FRAME_variable = NULL;
	static int ADD_NODE_CHANGE_COLOR_OBJECT_variable = NULL;
	static int ADD_NODE_CHANGE_FOV_variable = NULL;
	static int ADD_NODE_CHANGE_SIZE_X_variable = NULL;
	static int ADD_NODE_CHANGE_SIZE_Y_variable = NULL;
	static int ADD_NODE_CHANGE_SIZE_Z_variable = NULL;
	static int ADD_NODE_CHANGE_DIRECTION_ROTATE_MATRIX_variable = NULL;




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
	float setScaleCubeX();
	float setScaleCubeZ();
	template<typename U> U setPercentTexture() {
		ImGui::SliderFloat("percentTexture", &percentTexture, 0, 1);
	}
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
	void addNode(int typeOfNode);
	// button for add window
	void setNodeAddButtonWindow();

	// node editor
	void setStyleNodeFrame();
	void setNodeInformation(); // this fonction initialise the fps latence .ect
	void setNodeButtonFORadd(); // this fonction make the button for add  node
	void addNodeText(int variable,int& uniqueID, const char* text);
	void recevedNodeValueForSetNodeText();

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

