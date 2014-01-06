#include "HelloWorldScene.h"

using namespace cocos2d;

CCScene* HelloWorld::scene()
{
    CCScene * scene = NULL;
    do 
    {
        // 'scene' is an autorelease object
        scene = CCScene::create();
        CC_BREAK_IF(! scene);

        // 'layer' is an autorelease object
        HelloWorld *layer = HelloWorld::create();
        CC_BREAK_IF(! layer);

        // add layer as a child to scene
        scene->addChild(layer);
    } while (0);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    bool bRet = false;
    do 
    {
        //////////////////////////////////////////////////////////////////////////
        // super init first
        //////////////////////////////////////////////////////////////////////////

        CC_BREAK_IF(! CCLayer::init());


		sqlite3 *pdb=NULL;
		std::string path=CCFileUtils::sharedFileUtils()->getWriteablePath()+"save.db3";

		
		std::string sql;
		int result;
		result=sqlite3_open(path.c_str(),&pdb);
		if(result!=SQLITE_OK)
			CCLog("open database failed,  number%d",result);

		//创建表
		result=sqlite3_exec(pdb,"create table student(ID integer primary key autoincrement,name text,sex text)",NULL,NULL,NULL);
		if(result!=SQLITE_OK)
			CCLog("create table failed");

		//插入数据
		sql="insert into student  values(1,'zhycheng','male')";
		result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
		if(result!=SQLITE_OK)
			CCLog("insert data failed!");


		//插入数据
		sql="insert into student  values(2,'liuyali','female')";
		result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
		if(result!=SQLITE_OK)
			CCLog("insert data failed!");

		sql="insert into student  values(3,'zhy_cheng','male')";
		result=sqlite3_exec(pdb,sql.c_str(),NULL,NULL,NULL);
		if(result!=SQLITE_OK)
			CCLog("insert data failed!");

		//删除数据
		//sql="delete from student where ID=1";
		//result=sqlite3_exec(pdb,sql.c_str(), ,NULL,NULL);
		//if(result!=SQLITE_OK)
		//	CCLog("delete data failed!");


		
		char **re;

		int r,c;
		
		sqlite3_get_table(pdb,"select * from student",&re,&r,&c,NULL);

		CCLog("row is %d,column is %d",r,c);

		CCLabelTTF *liu=CCLabelTTF::create(re[2*c+1],"Arial",24);
		liu->setPosition(ccp(200,200));
		addChild(liu,1);
		CCLog(re[2*c+1]);


		sqlite3_free_table(re);

		sqlite3_close(pdb);

		//CCDictionary *dictionary=CCDictionary::createWithContentsOfFile("test.xml");
		//const char *chinese=((CCString *)dictionary->objectForKey("japanese"))->m_sString.c_str();
		//CCLabelTTF *ccc=CCLabelTTF::create(chinese,"Arial",24);
		//ccc->setPosition(ccp(300,300));
		///addChild(ccc,1);
		///const char *path=CCFileUtils::sharedFileUtils()->getResourceDirectory();
		///CCLog("%s",path);

        bRet = true;
    } while (0);

    return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
    // "close" menu item clicked
    CCDirector::sharedDirector()->end();
}

