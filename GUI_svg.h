#ifndef GUI_SVG_H_INCLUDED
#define GUI_SVG_H_INCLUDED
#define PATHFILE "/.TempSvgFile"
#include<dirent.h>
#include"../tinyxml_2_6_2/tinyxml/tinystr.h"
#include"../tinyxml_2_6_2/tinyxml/tinyxml.h"

class GUI_svg:public GUI_Texture
{
private:
    char tmp[255];
    TiXmlDocument doc;
    TiXmlElement *svg;
    SDL_Renderer *gRenderCopy;
    bool isInit=false;
    std::string fileSvgSave="";
public:
    void Init(){
        if(!isInit){
            fileSvgSave=SDL_getenv("temp");
            fileSvgSave+=PATHFILE;
            mkdir(fileSvgSave.c_str());
            sprintf(tmp,"%s%s",fileSvgSave.c_str(),"/tempSvgFile.svg");
            fileSvgSave=tmp;
        }else{
            std::cout<<"deja fait"<<std::endl;
        }
    }

    /**   @brief : GUI_svg
        *   @param : -x,y : position du svgImage
        *   @param : -rendu : Le Rendu Affichage Du cercle
    */
    GUI_svg(SDL_Renderer *rendu,int x,int y)
    {
        this->ID=W_SVG;
        gRect.x=x;
        gRect.y=y;
        Init();
        gRenderCopy=rendu;

    }

    ~GUI_svg()
    {
        delete []tmp;
    }

    /**   @brief : GUI_svg
        *   @param : -x,y : position du svgImage
        *   @param : -w,h : taille du svgImage
        *   @param : -WriteDraw : fichier d'ecriture dans le SVG
        *   @param : -rendu : Le Rendu Affichage Du cercle
    */
    GUI_svg(SDL_Renderer *rendu,std::string WriteDraw,int x,int y)
    {
        this->ID=W_SVG;
        Init();
        std::ofstream fileSave(fileSvgSave.c_str());
        fileSave<<WriteDraw<<std::endl;
        fileSave.close();
        gTexture=SDL_CreateTextureFromSurface(rendu,IMG_Load(fileSvgSave.c_str()));
        if(gTexture==NULL)
        {
            std::cout<<IMG_GetError()<<std::endl;
            exit(EXIT_FAILURE);
        }
        gRect.x=x;
        gRect.y=y;
        UpdateSizeTexture();
        remove(fileSvgSave.c_str());
    }
    void setColor(SDL_Color col){
        SDL_SetTextureColorMod(gTexture,col.r,col.g,col.b);
    }

    /**   @brief : CreateSvgHeader
      *   @param : -w,h : taille du viewport du svg
    */
    void CreateSvgHeader(int w,int h)
    {
        TiXmlDeclaration *decl=new TiXmlDeclaration("1.0","UTF-8","");
        doc.LinkEndChild(decl);
        svg=new TiXmlElement("svg");
        svg->SetAttribute("xmlns","http://www.w3.org/2000/svg");//<svg xmlns="http://www.w3.org/2000/svg" fill = "none" width="3*r" height="3*r">
        svg->SetAttribute("fill","none");
        svg->SetAttribute("width",w);
        svg->SetAttribute("height",h);
        doc.LinkEndChild(svg);
    }

    /**   @brief : SaveAndLoad
      *   fonction de sauegarde de svg
    */
    void SaveAndLoad()
    {
        //La sauvegarde Du fichier SVG
        doc.SaveFile(fileSvgSave.c_str());

        //chargement du fichier SVG Creer
        gTexture=SDL_CreateTextureFromSurface(gRenderCopy,IMG_Load(fileSvgSave.c_str()));

        //Suppression du fichier Svg Creer
        remove(fileSvgSave.c_str());

        UpdateSizeTexture();
    }


    /**   @brief : DrawCircle
      *   fonction de dessing d'un cercle simple
    */
    void DrawCircle(int r,float strokeWidth=1,std::string colHexBordure="#000",bool isfill=false,std::string colHexFill="#fff")
    {

        CreateSvgHeader(2*r+2*strokeWidth,2*r+2*strokeWidth);

        //Creation Du Cercle

        TiXmlElement *circle=new TiXmlElement("circle");//<circle/>
        circle->SetAttribute("cx",r+strokeWidth);//<circle cx="r+strokeWidth" //pour la positon ( affichage )en X du cercle
        circle->SetAttribute("cy",r+strokeWidth);//<circle cy="r+strokeWidth" //pour la positon ( affichage )en Y du cercle
        circle->SetAttribute("r",r);//<circle r="r" //pour le rayon du cercle
        circle->SetAttribute("stroke",colHexBordure.c_str());//<circle stroke=#000 //pour la  couleur de bordure
        circle->SetDoubleAttribute("stroke-width",strokeWidth);//<circle stroke-width=strokeWidth //pour la largeur de bordure

        //Booleen de Verification de Remplisage
        if(isfill)
        {
            //si Oui
            circle->SetAttribute("fill",colHexFill.c_str());
        }
        else
        {

            //Si non
            circle->SetAttribute("fill","none");
        }

        //<circle stroke=#000/></svg>
        svg->LinkEndChild(circle);

        SaveAndLoad();

    }

    /**   @brief : DrawDoubleCircle
      *   fonction de dessing d'un double cercle simple
    */
    void DrawDoubleCircle(int r1,int r2,float strokeWidthC1=1,float strokeWidthC2=1,bool isfillC1=false,bool isfillC2=false,std::string colHexBordureC1="#000",std::string colHexBordureC2="#000",std::string colHexFillC1="#000",std::string colHexFillC2="#000")
    {

        CreateSvgHeader(2*(r1>r2?r1+strokeWidthC1:r2+strokeWidthC2),2*(r1>r2?r1+strokeWidthC1*2:r2+strokeWidthC2*2));

        //Premier Cercle
        TiXmlElement *circle=new TiXmlElement("circle");//<circle/>
        circle->SetAttribute("cx",r1+strokeWidthC1);//<circle cx="r+strokeWidth" //pour la positon ( affichage )en X du cercle
        circle->SetAttribute("cy",r1+strokeWidthC1);//<circle cy="r+strokeWidth" //pour la positon ( affichage )en Y du cercle
        circle->SetAttribute("r",r1);//<circle r="r" //pour le rayon du cercle
        circle->SetAttribute("stroke",colHexBordureC1.c_str());//<circle stroke=#000 //pour la  couleur de bordure
        circle->SetDoubleAttribute("stroke-width",strokeWidthC1);//<circle stroke-width=strokeWidth //pour la largeur de bordure
        //Booleen de Verification de Remplisage
        if(isfillC1)
        {
            //si Oui
            circle->SetAttribute("fill",colHexFillC1.c_str());
        }
        else
        {
            //Si non
            circle->SetAttribute("fill","none");
        }

        svg->LinkEndChild(circle);

        // cercle a l'interieur
        TiXmlElement *circleII=new TiXmlElement("circle");//<circle/>
        circleII->SetAttribute("cx",r1+strokeWidthC1);//<circle cx="r+strokeWidth" //pour la positon ( affichage )en X du cercle
        circleII->SetAttribute("cy",r1+strokeWidthC1);//<circle cy="r+strokeWidth" //pour la positon ( affichage )en Y du cercle
        circleII->SetAttribute("r",r2);//<circle r="r" //pour le rayon du cercle
        circleII->SetAttribute("stroke",colHexBordureC2.c_str());//<circle stroke=#000 //pour la  couleur de bordure
        circleII->SetDoubleAttribute("stroke-width",strokeWidthC2);//<circle stroke-width=strokeWidth //pour la largeur de bordure

        //Booleen de Verification de Remplisage
        if(isfillC2)
        {
            //si Oui
            circleII->SetAttribute("fill",colHexFillC2.c_str());
        }
        else
        {

            //Si non
            circleII->SetAttribute("fill","none");
        }

        //<circle stroke=#000/></svg>
        svg->LinkEndChild(circleII);

        SaveAndLoad();
    }

    /**   @brief : DrawTriangle
      *   fonction de dessing d'un triangle simple
    */
    void DrawTriangle(int hauteur,int base,float strokeWidth=1,std::string colHexBordure="#000",bool isfill=false,std::string colHexFill="#fff")
    {
        CreateSvgHeader(base,hauteur);

        char tnum[255];
        ///changement ppolygonPoints (cas d'un Triangle Equilaterale (depandant de la base

        sprintf(tnum,"%d,%d,%d,%d,%d,%d",0,hauteur,base,hauteur,base/2,0);

        TiXmlElement *triangle=new TiXmlElement("polygon");//<polygon/>
        triangle->SetAttribute("points",tnum);
        triangle->SetAttribute("stroke",colHexBordure.c_str());
        triangle->SetDoubleAttribute("stroke-width",strokeWidth);
        if(isfill) //Booleen de Verification de Remplisage
        {
            triangle->SetAttribute("fill",colHexFill.c_str());//si Oui
        }
        else
        {
            triangle->SetAttribute("fill","none");//Si non
        }
        svg->LinkEndChild(triangle);

        SaveAndLoad();
    }

    /**   @brief : DrawRectangle
      *   fonction de dessing d'un rectangle simple
    */
    void DrawRectangle(int w,int h,int cx=0,int cy=0,float strokeWidth=1,std::string colHexBordure="#000",bool isfill=false,std::string colHexFill="#fff")
    {
        CreateSvgHeader(w,h);

        TiXmlElement *rect=new TiXmlElement("rect");
        rect->SetAttribute("x",0);
        rect->SetAttribute("y",0);
        rect->SetAttribute("rx",cx);
        rect->SetAttribute("ry",cy);
        rect->SetAttribute("width",w);
        rect->SetAttribute("height",h);
        rect->SetAttribute("stroke",colHexBordure.c_str());
        rect->SetDoubleAttribute("stroke-width",strokeWidth);

        if(isfill) //Booleen de Verification de Remplisage
        {
            rect->SetAttribute("fill",colHexFill.c_str());//si Oui
        }
        else
        {
            rect->SetAttribute("fill","none");//Si non
        }
        svg->LinkEndChild(rect);

        SaveAndLoad();
    }

     /**   @brief : DrawThreeRect
      *   fonction de dessing d'un triplerectangle
    */
    void DrawThreeRect(int w,int h,int cx=0,int cy=0,int space=0,float strokeWidth=1,std::string colHexBordure="#000",bool isfill=false,std::string colHexFill="#fff")
    {
        CreateSvgHeader(w,3*(h+space));
        for(int i=0;i<3;i++){
            TiXmlElement *rect=new TiXmlElement("rect");
            rect->SetAttribute("x",0);
            rect->SetAttribute("y",(h+space)*i);
            rect->SetAttribute("rx",cx);
            rect->SetAttribute("ry",cy);
            rect->SetAttribute("width",w);
            rect->SetAttribute("height",h);
            rect->SetAttribute("stroke",colHexBordure.c_str());
            rect->SetDoubleAttribute("stroke-width",strokeWidth);

            if(isfill) //Booleen de Verification de Remplisage
            {
                rect->SetAttribute("fill",colHexFill.c_str());//si Oui
            }
            else
            {
                rect->SetAttribute("fill","none");//Si non
            }
            svg->LinkEndChild(rect);
        }

        SaveAndLoad();
    }

    /**   @brief : DrawCross
      *   fonction de dessing d'un croix
    */
    void DrawCross(int w,int h,float strokeWidth=1,std::string colHexBordure="#000")
    {
        CreateSvgHeader(w+strokeWidth,h+strokeWidth);

        TiXmlElement *line1=new TiXmlElement("line");
        line1->SetAttribute("x1",0);
        line1->SetAttribute("y1",0);
        line1->SetAttribute("x2",w);
        line1->SetAttribute("y2",h);
        line1->SetAttribute("stroke",colHexBordure.c_str());
        line1->SetDoubleAttribute("stroke-width",strokeWidth);

        svg->LinkEndChild(line1);

        //=========
        TiXmlElement *line2=new TiXmlElement("line");
        line2->SetAttribute("x1",w);
        line2->SetAttribute("y1",0);
        line2->SetAttribute("x2",0);
        line2->SetAttribute("y2",h);

        line2->SetAttribute("stroke",colHexBordure.c_str());
        line2->SetDoubleAttribute("stroke-width",strokeWidth);

        svg->LinkEndChild(line2);

        SaveAndLoad();
    }

    /**   @brief : DrawLine
      *   fonction de dessing d'une ligne
    */
    void DrawLine(int w,float strokeWidth=1,std::string colHexBordure="#000")
    {
        CreateSvgHeader(w,strokeWidth);

        TiXmlElement *line=new TiXmlElement("line");
        line->SetAttribute("x1",0);
        line->SetAttribute("y1",0);
        line->SetAttribute("x2",w);
        line->SetAttribute("y2",0);
        line->SetAttribute("stroke",colHexBordure.c_str());
        line->SetDoubleAttribute("stroke-width",strokeWidth);

        svg->LinkEndChild(line);

        SaveAndLoad();
    }
};
#endif // GUI_SVG_H_INCLUDED
