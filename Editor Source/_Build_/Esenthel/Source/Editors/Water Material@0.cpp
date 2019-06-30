﻿/******************************************************************************/
#include "stdafx.h"
/******************************************************************************/
WaterMtrlRegion WaterMtrlEdit;
/******************************************************************************/

/******************************************************************************/
      void WaterMtrlRegion::Change::create(ptr user)
{
         data=WaterMtrlEdit.edit;
         WaterMtrlEdit.undoVis();
      }
      void WaterMtrlRegion::Change::apply(ptr user)
{
         WaterMtrlEdit.edit.undo(data);
         WaterMtrlEdit.setChanged();
         WaterMtrlEdit.toGui();
         WaterMtrlEdit.undoVis();
      }
   void WaterMtrlRegion::Render() {WaterMtrlEdit.render();}
          void WaterMtrlRegion::render()
   {
      switch(Renderer())
      {
         case RM_PREPARE:
         {
            LightDir(previewLight(), 1-D.ambientColorL()).add(false);
         }break;
      }
   }
   void WaterMtrlRegion::drawPreview()
{
      preview_cam.set();

      CurrentEnvironment().set();
      MOTION_MODE  motion   =D.   motionMode(); D.   motionMode( MOTION_NONE);
      AMBIENT_MODE ambient  =D.  ambientMode(); D.  ambientMode(AMBIENT_FLAT);
      DOF_MODE     dof      =D.      dofMode(); D.      dofMode(    DOF_NONE);
      bool         eye_adapt=D.eyeAdaptation(); D.eyeAdaptation(       false);
      bool         astros   =AstrosDraw       ; AstrosDraw     =false;
      bool         ocean    =Water.draw       ; Water.draw     =true;

      WaterMtrl temp; Swap(temp, SCAST(WaterMtrl, Water)); SCAST(WaterMtrl, Water)=*game; PlaneM water_plane=Water.plane; Water.plane.set(Vec(0, -1, 0), Vec(0, 1, 0));

      Renderer(Render);

      Swap(temp, SCAST(WaterMtrl, Water)); Water.plane=water_plane;

      D.      dofMode(dof      );
      D.   motionMode(motion   );
      D.  ambientMode(ambient  );
      D.eyeAdaptation(eye_adapt);
      AstrosDraw=astros;
      Water.draw=ocean;
   }
   void WaterMtrlRegion::PreChanged(C Property &prop) {WaterMtrlEdit.undos.set(&prop);}
   void    WaterMtrlRegion::Changed(C Property &prop) {WaterMtrlEdit.setChanged();}
   Str  WaterMtrlRegion::Density(C WaterMtrlRegion &mr          ) {return mr.edit.density;}
   void WaterMtrlRegion::Density(  WaterMtrlRegion &mr, C Str &t) {mr.edit.density=TextFlt(t); mr.edit.density_time.getUTC();}
   Str  WaterMtrlRegion::DensityAdd(C WaterMtrlRegion &mr          ) {return mr.edit.density_add;}
   void WaterMtrlRegion::DensityAdd(  WaterMtrlRegion &mr, C Str &t) {mr.edit.density_add=TextFlt(t); mr.edit.density_time.getUTC();}
   Str  WaterMtrlRegion::DensityUnderwater(C WaterMtrlRegion &mr          ) {return mr.edit.density_underwater;}
   void WaterMtrlRegion::DensityUnderwater(  WaterMtrlRegion &mr, C Str &t) {mr.edit.density_underwater=TextFlt(t); mr.edit.density_underwater_time.getUTC();}
   Str  WaterMtrlRegion::DensityUnderwaterAdd(C WaterMtrlRegion &mr          ) {return mr.edit.density_underwater_add;}
   void WaterMtrlRegion::DensityUnderwaterAdd(  WaterMtrlRegion &mr, C Str &t) {mr.edit.density_underwater_add=TextFlt(t); mr.edit.density_underwater_time.getUTC();}
   Str  WaterMtrlRegion::ScaleColor(C WaterMtrlRegion &mr          ) {return mr.edit.scale_color;}
   void WaterMtrlRegion::ScaleColor(  WaterMtrlRegion &mr, C Str &t) {mr.edit.scale_color=TextFlt(t); mr.edit.scale_color_time.getUTC();}
   Str  WaterMtrlRegion::ScaleNormal(C WaterMtrlRegion &mr          ) {return mr.edit.scale_normal;}
   void WaterMtrlRegion::ScaleNormal(  WaterMtrlRegion &mr, C Str &t) {mr.edit.scale_normal=TextFlt(t); mr.edit.scale_normal_time.getUTC();}
   Str  WaterMtrlRegion::ScaleBump(C WaterMtrlRegion &mr          ) {return mr.edit.scale_bump;}
   void WaterMtrlRegion::ScaleBump(  WaterMtrlRegion &mr, C Str &t) {mr.edit.scale_bump=TextFlt(t); mr.edit.scale_bump_time.getUTC();}
   Str  WaterMtrlRegion::NrmScale(C WaterMtrlRegion &mr          ) {return mr.edit.rough;}
   void WaterMtrlRegion::NrmScale(  WaterMtrlRegion &mr, C Str &t) {mr.edit.rough=TextFlt(t); mr.edit.rough_bump_time.getUTC();}
   Str  WaterMtrlRegion::ReflectTex(C WaterMtrlRegion &mr          ) {return mr.edit.reflection;}
   void WaterMtrlRegion::ReflectTex(  WaterMtrlRegion &mr, C Str &t) {mr.edit.reflection=TextFlt(t); mr.edit.reflection_time.getUTC();}
   Str  WaterMtrlRegion::ReflectWorld(C WaterMtrlRegion &mr          ) {return mr.edit.reflect_world;}
   void WaterMtrlRegion::ReflectWorld(  WaterMtrlRegion &mr, C Str &t) {mr.edit.reflect_world=TextFlt(t); mr.edit.reflect_world_time.getUTC();}
   Str  WaterMtrlRegion::Refract(C WaterMtrlRegion &mr          ) {return mr.edit.refract;}
   void WaterMtrlRegion::Refract(  WaterMtrlRegion &mr, C Str &t) {mr.edit.refract=TextFlt(t); mr.edit.refract_time.getUTC();}
   Str  WaterMtrlRegion::RefractReflection(C WaterMtrlRegion &mr          ) {return mr.edit.refract_reflection;}
   void WaterMtrlRegion::RefractReflection(  WaterMtrlRegion &mr, C Str &t) {mr.edit.refract_reflection=TextFlt(t); mr.edit.refract_reflection_time.getUTC();}
   Str  WaterMtrlRegion::RefractUnderwater(C WaterMtrlRegion &mr          ) {return mr.edit.refract_underwater;}
   void WaterMtrlRegion::RefractUnderwater(  WaterMtrlRegion &mr, C Str &t) {mr.edit.refract_underwater=TextFlt(t); mr.edit.refract_underwater_time.getUTC();}
   Str  WaterMtrlRegion::Specular(C WaterMtrlRegion &mr          ) {return mr.edit.specular;}
   void WaterMtrlRegion::Specular(  WaterMtrlRegion &mr, C Str &t) {mr.edit.specular=TextFlt(t); mr.edit.spec_time.getUTC();}
   Str  WaterMtrlRegion::WaveScale(C WaterMtrlRegion &mr          ) {return mr.edit.wave_scale;}
   void WaterMtrlRegion::WaveScale(  WaterMtrlRegion &mr, C Str &t) {mr.edit.wave_scale=TextFlt(t); mr.edit.wave_scale_time.getUTC();}
   Str  WaterMtrlRegion::FresnelPow(C WaterMtrlRegion &mr          ) {return mr.edit.fresnel_pow;}
   void WaterMtrlRegion::FresnelPow(  WaterMtrlRegion &mr, C Str &t) {mr.edit.fresnel_pow=TextFlt(t); mr.edit.fresnel_pow_time.getUTC();}
   Str  WaterMtrlRegion::FresnelRough(C WaterMtrlRegion &mr          ) {return mr.edit.fresnel_rough;}
   void WaterMtrlRegion::FresnelRough(  WaterMtrlRegion &mr, C Str &t) {mr.edit.fresnel_rough=TextFlt(t); mr.edit.fresnel_rough_time.getUTC();}
   Str  WaterMtrlRegion::FresnelColor(C WaterMtrlRegion &mr          ) {return mr.edit.fresnel_color;}
   void WaterMtrlRegion::FresnelColor(  WaterMtrlRegion &mr, C Str &t) {mr.edit.fresnel_color=TextVec(t); mr.edit.fresnel_color_time.getUTC();}
   Str  WaterMtrlRegion::Col(C WaterMtrlRegion &mr          ) {return mr.edit.color;}
   void WaterMtrlRegion::Col(  WaterMtrlRegion &mr, C Str &t) {mr.edit.color.xyz=TextVec(t); mr.edit.color_time.getUTC();}
   Str  WaterMtrlRegion::ColorUnderwater0(C WaterMtrlRegion &mr          ) {return mr.edit.color_underwater0;}
   void WaterMtrlRegion::ColorUnderwater0(  WaterMtrlRegion &mr, C Str &t) {mr.edit.color_underwater0=TextVec(t); mr.edit.color_underwater_time.getUTC();}
   Str  WaterMtrlRegion::ColorUnderwater1(C WaterMtrlRegion &mr          ) {return mr.edit.color_underwater1;}
   void WaterMtrlRegion::ColorUnderwater1(  WaterMtrlRegion &mr, C Str &t) {mr.edit.color_underwater1=TextVec(t); mr.edit.color_underwater_time.getUTC();}
   Str  WaterMtrlRegion::FNY(C WaterMtrlRegion &mr          ) {return mr.edit.flip_normal_y;}
   void WaterMtrlRegion::FNY(  WaterMtrlRegion &mr, C Str &t) {uint base_tex=mr.edit.baseTex(); mr.edit.flip_normal_y=TextBool(t); mr.edit.flip_normal_y_time.getUTC(); mr.rebuildBase(base_tex, true, false);}
   EditMaterial& WaterMtrlRegion::getEditMtrl(){return edit;}
   C ImagePtr    & WaterMtrlRegion::getBase0(){return game->     colorMap();}
   C ImagePtr    & WaterMtrlRegion::getBase1(){return game->    normalMap();}
   C ImagePtr    & WaterMtrlRegion::getReflection(){return game->reflectionMap();}
   void WaterMtrlRegion::create()
   {
      undos.replaceClass<Change>();
      ::MaterialRegion::create(); elm_type=ELM_WATER_MTRL; max_zoom=50; preview_cam.dist=15; preview_cam.pitch=-PI_6; preview_cam.setSpherical(); set_mtrl.del(); brightness.del(); preview_mode.del(); preview_big.range=preview.range=200;

      flt e=0.01f, prop_height=0.044f;
      props.clear();
      props.New().create("Density"                 , MemberDesc(DATA_REAL).setFunc(Density              , Density              )).range(0, 1);
      props.New().create("Density Base"            , MemberDesc(DATA_REAL).setFunc(DensityAdd           , DensityAdd           )).range(0, 1);
      props.New().create("Density Underwater"      , MemberDesc(DATA_REAL).setFunc(DensityUnderwater    , DensityUnderwater    )).range(0, 1);
      props.New().create("Density Underwater Base" , MemberDesc(DATA_REAL).setFunc(DensityUnderwaterAdd , DensityUnderwaterAdd )).range(0, 1);
      props.New().create("Scale Color"             , MemberDesc(DATA_REAL).setFunc(ScaleColor           , ScaleColor           )).min(0).mouseEditMode(PROP_MOUSE_EDIT_SCALAR);
      props.New().create("Scale Normal"            , MemberDesc(DATA_REAL).setFunc(ScaleNormal          , ScaleNormal          )).min(0).mouseEditMode(PROP_MOUSE_EDIT_SCALAR);
      props.New().create("Scale Bump"              , MemberDesc(DATA_REAL).setFunc(ScaleBump            , ScaleBump            )).min(5).mouseEditMode(PROP_MOUSE_EDIT_SCALAR);
      props.New().create("Normal"                  , MemberDesc(DATA_REAL).setFunc(NrmScale             , NrmScale             )).range(0, 3);
      props.New().create("Flip Normal Y"           , MemberDesc(DATA_BOOL).setFunc(FNY                  , FNY                  ));
      props.New().create("Reflection from Texture" , MemberDesc(DATA_REAL).setFunc(ReflectTex           , ReflectTex           )).range(0, 1).mouseEditSpeed(0.5f);
      props.New().create("Reflection from World"   , MemberDesc(DATA_REAL).setFunc(ReflectWorld         , ReflectWorld         )).range(0, 1);
      props.New().create("Refraction"              , MemberDesc(DATA_REAL).setFunc(Refract              , Refract              )).range(0, 0.50f).mouseEditSpeed(0.25f);
      props.New().create("Refraction of Reflection", MemberDesc(DATA_REAL).setFunc(RefractReflection    , RefractReflection    )).range(0, 0.25f).mouseEditSpeed(0.10f);
      props.New().create("Refraction Underwater"   , MemberDesc(DATA_REAL).setFunc(RefractUnderwater    , RefractUnderwater    )).range(0, 0.04f).mouseEditSpeed(0.02f);
      props.New().create("Specular"                , MemberDesc(DATA_REAL).setFunc(Specular             , Specular             )).min(0);
      props.New().create("Vertical Wave Scale"     , MemberDesc(DATA_REAL).setFunc(WaveScale            , WaveScale            )).range(0, 1);
      props.New().create("Fresnel Term Power"      , MemberDesc(DATA_REAL).setFunc(FresnelPow           , FresnelPow           )).min(0);
      props.New().create("Fresnel Term Roughness"  , MemberDesc(DATA_REAL).setFunc(FresnelRough         , FresnelRough         )).min(0);
      props.New().create("Fresnel Term Color"      , MemberDesc(DATA_VEC ).setFunc(FresnelColor         , FresnelColor         )).setColor();
      props.New().create("Color"                   , MemberDesc(DATA_VEC ).setFunc(Col                  , Col                  )).setColor();
      props.New().create("Underwater Surface Color", MemberDesc(DATA_VEC ).setFunc(ColorUnderwater0     , ColorUnderwater0     )).setColor();
      props.New().create("Underwater Depths Color" , MemberDesc(DATA_VEC ).setFunc(ColorUnderwater1     , ColorUnderwater1     )).setColor();

      Rect prop_rect=AddProperties(props, sub, 0, prop_height, 0.135f, &ts); REPAO(props).autoData(this).changed(Changed, PreChanged);

      flt tex_size=prop_height*3; int i=0;
      texs.clear();
      sub+=texs.New().create(TEX_COLOR  , MEMBER(EditWaterMtrl,      color_map), MEMBER(EditWaterMtrl,      color_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Color"         , T); i-=3;
      sub+=texs.New().create(TEX_BUMP   , MEMBER(EditWaterMtrl,       bump_map), MEMBER(EditWaterMtrl,       bump_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Bump"          , T); i-=3;
      sub+=texs.New().create(TEX_NORMAL , MEMBER(EditWaterMtrl,     normal_map), MEMBER(EditWaterMtrl,     normal_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Normal"        , T); i-=3*4-2;
      sub+=texs.New().create(TEX_RFL_U  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Reflect\nUp"   , T); i-=3;
      sub+=texs.New().create(TEX_RFL_D  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Reflect\nDown" , T); i-=3;
      sub+=texs.New().create(TEX_RFL_ALL, MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*4, i*prop_height), tex_size, tex_size), "Reflect\nAll"  , T);
      sub+=texs.New().create(TEX_RFL_L  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*3, i*prop_height), tex_size, tex_size), "Reflect\nLeft" , T);
      sub+=texs.New().create(TEX_RFL_F  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*2, i*prop_height), tex_size, tex_size), "Reflect\nFront", T);
      sub+=texs.New().create(TEX_RFL_R  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*1, i*prop_height), tex_size, tex_size), "Reflect\nRight", T);
      sub+=texs.New().create(TEX_RFL_B  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e+tex_size*0, i*prop_height), tex_size, tex_size), "Reflect\nBack" , T); i-=3;
      REPA(texs){sub+=texs[i].remove; prop_rect|=texs[i].rect();}

      setBottom(prop_rect);
   }
   void WaterMtrlRegion::flush()
{
      if(elm && game && changed)
      {
         if(ElmWaterMtrl *data=elm->waterMtrlData()){data->newVer(); data->from(edit);} // modify just before saving/sending in case we've received data from server after edit
         Save( edit, Proj.editPath(*elm   )); edit.copyTo(*game, Proj);
         Save(*game, Proj.gamePath( elm->id)); Proj.savedGame(*elm);
         Proj.mtrlSetAutoTanBin(elm->id);
         Server.setElmLong(elm->id);
      }
      changed=false;
   }
   void WaterMtrlRegion::setChanged()
{
      if(elm && game)
      {
         changed=true;
         if(ElmWaterMtrl *data=elm->waterMtrlData()){data->newVer(); data->from(edit);}
         edit.copyTo(*game, Proj);
      }
   }
   void WaterMtrlRegion::set(Elm *elm)
{
      if(elm && elm->type!=ELM_WATER_MTRL)elm=null;
      if(T.elm!=elm)
      {
         flush();
         undos.del(); undoVis();
         if(elm)game=     Proj.gamePath( elm->id) ;else game=&temp;
         if(elm)edit.load(Proj.editPath(*elm   ));else edit.reset();
         T.elm   =elm;
         T.elm_id=(elm ? elm->id : UIDZero);
         toGui();
         Proj.refresh(false, false);
         if(!elm)
         {
            MaterialRegion &other=((this==&MtrlEdit) ? WaterMtrlEdit : MtrlEdit);
            hide(); if(other.elm)other.show();
         }
      }
   }
   void WaterMtrlRegion::set(C WaterMtrlPtr &mtrl) {activate(Proj.findElm(mtrl.id()));}
   void WaterMtrlRegion::rebuildBase(uint old_base_tex, bool changed_flip_normal_y, bool adjust_params, bool always)
{
      if(elm && game)
      {
         if(auto_reload || always)
         {
            Proj.mtrlCreateBaseTextures(edit, changed_flip_normal_y);
            Time.skipUpdate(); // compressing textures can be slow
         }
         setChanged();

         toGui();
      }
   }
   void WaterMtrlRegion::rebuildReflection()
{
      if(elm && game)
      {
         Proj.mtrlCreateReflectionTexture(edit);
         setChanged();
         Time.skipUpdate(); // compressing textures can be slow

         toGui();
      }
   }
   void WaterMtrlRegion::rebuildDetail()
{
   }
   void WaterMtrlRegion::rebuildMacro()
{
   }
   void WaterMtrlRegion::rebuildLight()
{
   }
   void WaterMtrlRegion::elmChanged(C UID &mtrl_id)
{
      if(elm && elm->id==mtrl_id)
      {
         undos.set(null, true);
         EditWaterMtrl temp; if(temp.load(Proj.editPath(*elm)))if(edit.sync(temp)){edit.copyTo(*game, Proj); toGui();}
      }
   }
WaterMtrlRegion::WaterMtrlRegion() : game(&temp) {}

/******************************************************************************/
