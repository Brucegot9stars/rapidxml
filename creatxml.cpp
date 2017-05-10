//#include "stdafx.h"
//g++ -o crxml creatxml.cpp -I./rapidxml
#include <cstdlib>
#include <iostream>


//下面三个文件是本段代码需要的库文件
#include "rapidxml/rapidxml.hpp"       
#include "rapidxml/rapidxml_utils.hpp"
#include "rapidxml/rapidxml_print.hpp"


int CreateXml();
int ReadAndChangeXml();
int main(int argc, char* argv[])
{
    //测试用例
    //CreateXml();
    //测试用例
    ReadAndChangeXml();
   
    return 0;
}
//创建一个名称为config2.xml文件
int CreateXml()
{
    rapidxml::xml_document<> doc;
    	
    rapidxml::xml_node<>* rot = doc.allocate_node(rapidxml::node_pi,doc.allocate_string("xml version='1.0' encoding='utf-8'"));
    doc.append_node(rot);
    
    rapidxml::xml_node<>* node = doc.allocate_node(rapidxml::node_element,"config","information");
    doc.append_node(node);
    
    rapidxml::xml_node<>* color = doc.allocate_node(rapidxml::node_element,"color",NULL);
    node->append_node(color);
    color->append_node(doc.allocate_node(rapidxml::node_element,"red","0.1"));
    color->append_node(doc.allocate_node(rapidxml::node_element,"green","0.1"));
    color->append_node(doc.allocate_node(rapidxml::node_element,"blue","0.1"));
    color->append_node(doc.allocate_node(rapidxml::node_element,"alpha","1.0"));
    	
    rapidxml::xml_node<>* size = doc.allocate_node(rapidxml::node_element,"size",NULL);
    size->append_node(doc.allocate_node(rapidxml::node_element,"x","640"));
    size->append_node(doc.allocate_node(rapidxml::node_element,"y","480"));
    node->append_node(size);
    
    rapidxml::xml_node<>* mode = doc.allocate_node(rapidxml::node_element,"mode","screen mode");
    mode->append_attribute(doc.allocate_attribute("fullscreen","false"));
    node->append_node(mode);
    std::string text;
    rapidxml::print(std::back_inserter(text), doc, 0);
    std::cout<<text<<std::endl;
    std::ofstream out("./config1.xml");
    out << doc;
		

    return 0;
}




//读取并修改config3.xml
int ReadAndChangeXml()
{
     rapidxml::file<> fdoc("./config1.xml");
     //读文件，写屏幕
     //std::cout<<fdoc.data()<<std::endl;
     	
     //define a xml file	
     rapidxml::xml_document<> doc;
     doc.parse<0>(fdoc.data());
     std::cout<<doc.name()<<std::endl;
     
     //! 获取根节点,打印根节点名称
     rapidxml::xml_node<>* root = doc.first_node();
     std::cout<<root->name()<<std::endl;
     //! 获取根节点第一个节点，打印第一个节点的名称
     rapidxml::xml_node<>* node1 = root->first_node();
     std::cout<<node1->name()<<std::endl;
     	
     	//打印第一个节点下的第一个节点的名称和值  red 01
     rapidxml::xml_node<>* node11 = node1->first_node();
     std::cout<<node11->name()<<std::endl;
     std::cout<<node11->value()<<std::endl;
     	
     //! 修改之后再次保存
     rapidxml::xml_node<>* size = root->first_node("size");
     //size节点下添加两个节点
     size->append_node(doc.allocate_node(rapidxml::node_element,"h","720"));
     size->append_node(doc.allocate_node(rapidxml::node_element,"w","1080"));
     std::string text;
     rapidxml::print(std::back_inserter(text),doc,0);
     std::cout<<text<<std::endl;
     //输出生成新的文件
     std::ofstream out("./config2.xml");
     out << doc;
   
     return 0;
}