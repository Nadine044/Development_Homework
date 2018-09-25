#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1Scene;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	// Called before render is available
	bool Awake()
	{
		// TODO 3: Load config.xml file using load_file() method from the xml_document class.
		// If everything goes well, load the top tag inside the xml_node property
		// created in the last TODO

		pugi::xml_parse_result result = doc1.load_file("../Motor2D/config.xml");
		if (result)
		{
			LOG("Parse error: ", result.description());
			node1 = doc1.child("config");
		}

			bool ret = true;

		p2List_item<j1Module*>* item;
		item = modules.start;

		while (item != NULL && ret == true)
		{
			// TODO 6: Add a new argument to the Awake method to receive a pointer to a xml node.
			// If the section with the module name exist in config.xml, fill the pointer with the address of a valid xml_node
			// that can be used to read all variables from that section. Send nullptr if the section does not exist in config.xml



			ret = item->data->Awake();
			item = item->next;
		}

		return ret;
	}

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;

private:

	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1Scene*			scene;

	pugi::xml_node node1;
	pugi::xml_document doc1;


private:

	p2List<j1Module*>	modules;
	uint				frames;
	float				dt;

	// TODO 2: Create two new variables from pugui namespace:
	// a xml_document to store the while config file and
	// a xml_node to read specific branches of the xml

	
	

	int					argc;
	char**				args;
};

extern j1App* App; 

#endif