#include "FsFaeris.h" 
#include "FsGlobal.h"
#include "FsLuaEngine.h"


FS_USE_MAIN_ENTRY 

NS_FS_BEGIN 

void  FsMain_Entry(int argc,char** argv)
{
	if(argc<3)
	{
		printf("useage %d <workdir> <filename>\n",argv[0]);
		exit(0);
	}

	FsFaeris_LoadConfig((const char*)NULL);
	VFS::setRoot(argv[1]);
	LuaEngine* engine=LuaEngine::create();
	FS_NO_REF_DESTROY(engine);
	Global::setScriptEngine(engine);

	FsDict* dict=Global::felisScriptMgr()->loadDict(argv[2]);
	if(dict==NULL)
	{
		printf("can't load file(%s) to dict\n",argv[2]);
		exit(0);
	}

	int width=1024;
	int height=800;

	ScriptUtil::getInteger(dict,"winWidth",&width);
	ScriptUtil::getInteger(dict,"winHeight",&height);

	Global::window()->setSize(width,height);


	FsObject* ob=Global::classMgr()->newInstance(dict);
	if(ob==NULL)
	{
		printf("can't create Fsobject From file(%s)\n",argv[2]);
		exit(0);
	}

	Scene* sn=dynamic_cast<Scene*>(ob);
	if(sn==NULL)
	{
		printf("file(%s) is not scene\n",argv[2]);
		exit(0);
	}
	


	Global::director()->run(sn);
	Global::scheduler()->setFps(0);

}


NS_FS_END
