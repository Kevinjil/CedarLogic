
#pragma once
#include "../../klsCollisionChecker.h"
#include <string>
#include <map>
#include <vector>
#include "../../gl_defs.h"

class wxCommandProcessor;
class gateHotspot;
class guiWire;
class Message_SET_GATE_PARAM;
class XMLParser;

class guiGate : public klsCollisionObject {
public:
	guiGate();

	virtual ~guiGate();

	void setID(long nid);

	unsigned long getID();

	void setLibraryName(std::string nLibName, std::string nLibGateName);

	std::string getLibraryName();

	std::string getLibraryGateName();

	std::string getLogicType();

	std::string getGUIType();

	virtual void draw(bool color = true);

	void setGLcoords(float x, float y, bool noUpdateWires = false);

	void getGLcoords(float &x, float &y);

	// Shift the gate by x and y, relative to its current location:
	void translateGLcoords(float x, float y);

	// Function to show the gate's parameters dialog, takes the command
	//	processor object to assign the setparameters command to.  gc is
	//	a GUICircuit pointer
	virtual void doParamsDialog(void* gc, wxCommandProcessor* wxcmd);

	// Make all connections end their drag so segments are merged
	void finalizeWirePlacements();

	// Set and get param virtual functions, simply assigns a string
	virtual void setGUIParam(std::string paramName, std::string value);

	virtual std::string getGUIParam(std::string paramName);

	std::map < std::string, std::string >* getAllGUIParams();

	virtual void setLogicParam(std::string paramName, std::string value);

	virtual std::string getLogicParam(std::string paramName);

	std::map < std::string, std::string >* getAllLogicParams();

	void declareInput(std::string name);

	void declareOutput(std::string name);

	// Draw this gate as unselected:
	void unselect();

	void select();

	// Needed for toggles and keypads, maybe others; returns a message to be passed
	//	from a click.
	virtual Message_SET_GATE_PARAM* checkClick(GLfloat x, GLfloat y);

	// Draw this gate as selected from now until unselect() is
	// called, if the coordinate passed to it is within
	// this gate's bounding box in GL coordinates.
	// Return true if this gate is selected.
	bool clickSelect(GLfloat x, GLfloat y);

	// Insert a line in the line list.
	void insertLine(float x1, float y1, float x2, float y2);

	// Recalculate the bounding box, based on the lines that are included alredy:
	virtual void calcBBox(void);

	// Insert a hotspot in the hotspot list.
	void insertHotspot(float x1, float y1, std::string connection, int busLines);

	// Check if any of the hotspots of this gate are within the delta
	// of the world coordinates sX and sY. delta is in gl coords.
	std::string checkHotspots(GLfloat x, GLfloat y, GLfloat delta);

	// Return the coordinates of the hotspot in GL world-space coords.
	void getHotspotCoords(std::string hsName, float &x, float &y);

	// Get the name of the hotspot that overlaps the one given.
	// Return "" for no overlap or bad hotspot name.
	std::string getHotspotPal(const std::string &hotspot);

	// Is a particular hotspot aligned to the vertical or horizontal edge?
	bool isVerticalHotspot(std::string hsName);

	// Update all wires connected to me
	// Update the connected wires' shapes to accomidate the new gate position:
	void updateConnectionMerges();

	klsBBox getModelBBox();

	// Get a hotspot from its name.
	gateHotspot * getHotspot(const std::string &hotspotName);

	void addConnection(std::string, guiWire*);

	guiWire* getConnection(std::string hotspot);

	void removeConnection(std::string, int&);

	bool isConnected(std::string);

	bool isSelected();

	bool isConnectionInput(std::string idx);

	void saveGate(XMLParser*);

	virtual void saveGateTypeSpecifics(XMLParser* xparse);

	// Return the map of hotspot names to their coordinates:
	std::map<std::string, GLPoint2f> getHotspotList();


protected:

	// Convert model->world coordinates:
	GLPoint2f modelToWorld(GLPoint2f c);

	// Get a world-space bounding box:
	klsBBox getWorldBBox(void) { return this->getBBox(); };

	void updateBBoxes(bool noUpdateWires = false);

	std::string libName;

	std::string libGateName;

	GLdouble mModel[16];

	long gateID;

	std::string gateType;

	std::string guiGateType;

	GLfloat myX, myY;

	bool selected; // Is this gate selected or not?

				   // Model space bounding box:
	klsBBox modelBBox;

	std::vector<GLPoint2f> vertices;

	// map i/o name to hotspot coord
	std::map< std::string, gateHotspot* > hotspots;

	// map i/o name to wire id
	std::map< std::string, guiWire* > connections;

	// map i/o name to status as input (true = input, false = output)
	std::map< std::string, bool > isInput;

	// map param name to value
	std::map< std::string, std::string > gparams;	// GUI params

	std::map< std::string, std::string > lparams;  // Logic params
};