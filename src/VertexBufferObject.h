#ifndef DEF_VERTEXBUFFEROBJECT
#define DEF_VERTEXBUFFEROBJECT

// Include OpenGl

#include <GL\glew.h>

// Includes 
#include <Windows.h>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <sstream>
#include <queue>
#include <map>
#include <set>
#include <cstdint>

// Classe VertexBufferObject

class VertexBufferObject
{
public:
	void createVBO(int a_iSize = 0);
	void releaseVBO();

	void* mapBufferToMemory(int iUsageHint);
	void* mapSubBufferToMemory(int iUsageHint, UINT uiOffset, UINT uiLength);
	void unmapBuffer();

	void bindVBO(int a_iBufferType = GL_ARRAY_BUFFER);
	void uploadDataToGPU(int iUsageHint);

	void addData(void* ptrData, UINT uiDataSize);

	void* getDataPointer();
	UINT getBuffer();

	VertexBufferObject();

private:
	UINT uiBuffer;
	int iSize;
	int iBufferType;
	std::vector<BYTE> data;

	bool bDataUploaded;
};



#endif
