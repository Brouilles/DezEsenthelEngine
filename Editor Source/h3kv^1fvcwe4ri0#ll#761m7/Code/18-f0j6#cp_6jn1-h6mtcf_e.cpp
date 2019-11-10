/******************************************************************************/
class WaterMtrlRegion : MaterialRegion
{
   class Change : MaterialRegion.Change
   {
      EditWaterMtrl data;

      virtual void create(ptr user)override
      {
         data=WaterMtrlEdit.edit;
         WaterMtrlEdit.undoVis();
      }
      virtual void apply(ptr user)override
      {
         WaterMtrlEdit.edit.undo(data);
         WaterMtrlEdit.setChanged();
         WaterMtrlEdit.toGui();
         WaterMtrlEdit.undoVis();
      }
   }

   WaterMtrl     temp;
   WaterMtrlPtr  game=&temp;
   EditWaterMtrl edit;

   static void Render() {WaterMtrlEdit.render();}
          void render()
   {
      switch(Renderer())
      {
         case RM_PREPARE:
         {
            LightDir(previewLight(), 1-D.ambientColorL()).add(false);
         }break;
      }
   }
   virtual void drawPreview()override
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

   static void PreChanged(C Property &prop) {WaterMtrlEdit.undos.set(&prop);}
   static void    Changed(C Property &prop) {WaterMtrlEdit.setChanged();}

   static Str  Col      (C WaterMtrlRegion &mr          ) {return mr.edit.color_s;}
   static void Col      (  WaterMtrlRegion &mr, C Str &t) {mr.edit.color_s.xyz=TextVec(t); mr.edit.color_time.getUTC();}
   static Str  Smooth   (C WaterMtrlRegion &mr          ) {return mr.edit.smooth;}
   static void Smooth   (  WaterMtrlRegion &mr, C Str &t) {mr.edit.smooth=TextFlt(t); mr.edit.smooth_time.getUTC();}
   static Str  Reflect  (C WaterMtrlRegion &mr          ) {return mr.edit.reflect;}
   static void Reflect  (  WaterMtrlRegion &mr, C Str &t) {mr.edit.reflect=TextFlt(t); mr.edit.reflect_time.getUTC();}
   static Str  NrmScale (C WaterMtrlRegion &mr          ) {return mr.edit.normal;}
   static void NrmScale (  WaterMtrlRegion &mr, C Str &t) {mr.edit.normal=TextFlt(t); mr.edit.normal_time.getUTC();}
   static Str  FNY      (C WaterMtrlRegion &mr          ) {return mr.edit.flip_normal_y;}
   static void FNY      (  WaterMtrlRegion &mr, C Str &t) {uint base_tex=mr.edit.baseTex(); mr.edit.flip_normal_y=TextBool(t); mr.edit.flip_normal_y_time.getUTC(); mr.rebuildBase(base_tex, true, false);}
   static Str  WaveScale(C WaterMtrlRegion &mr          ) {return mr.edit.wave_scale;}
   static void WaveScale(  WaterMtrlRegion &mr, C Str &t) {mr.edit.wave_scale=TextFlt(t); mr.edit.wave_scale_time.getUTC();}

   static Str  ScaleColor (C WaterMtrlRegion &mr          ) {return 1/mr.edit.scale_color;}
   static void ScaleColor (  WaterMtrlRegion &mr, C Str &t) {mr.edit.scale_color=1/TextFlt(t); mr.edit.scale_color_time.getUTC();}
   static Str  ScaleNormal(C WaterMtrlRegion &mr          ) {return 1/mr.edit.scale_normal;}
   static void ScaleNormal(  WaterMtrlRegion &mr, C Str &t) {mr.edit.scale_normal=1/TextFlt(t); mr.edit.scale_normal_time.getUTC();}
   static Str  ScaleBump  (C WaterMtrlRegion &mr          ) {return 1/mr.edit.scale_bump;}
   static void ScaleBump  (  WaterMtrlRegion &mr, C Str &t) {mr.edit.scale_bump=1/TextFlt(t); mr.edit.scale_bump_time.getUTC();}

   static Str  Density   (C WaterMtrlRegion &mr          ) {return mr.edit.density;}
   static void Density   (  WaterMtrlRegion &mr, C Str &t) {mr.edit.density=TextFlt(t); mr.edit.density_time.getUTC();}
   static Str  DensityAdd(C WaterMtrlRegion &mr          ) {return mr.edit.density_add;}
   static void DensityAdd(  WaterMtrlRegion &mr, C Str &t) {mr.edit.density_add=TextFlt(t); mr.edit.density_time.getUTC();}

   static Str  Refract          (C WaterMtrlRegion &mr          ) {return mr.edit.refract;}
   static void Refract          (  WaterMtrlRegion &mr, C Str &t) {mr.edit.refract=TextFlt(t); mr.edit.refract_time.getUTC();}
   static Str  RefractReflection(C WaterMtrlRegion &mr          ) {return mr.edit.refract_reflection;}
   static void RefractReflection(  WaterMtrlRegion &mr, C Str &t) {mr.edit.refract_reflection=TextFlt(t); mr.edit.refract_reflection_time.getUTC();}

   static Str  ColorUnderwater0(C WaterMtrlRegion &mr          ) {return mr.edit.color_underwater0;}
   static void ColorUnderwater0(  WaterMtrlRegion &mr, C Str &t) {mr.edit.color_underwater0=TextVec(t); mr.edit.color_underwater_time.getUTC();}
   static Str  ColorUnderwater1(C WaterMtrlRegion &mr          ) {return mr.edit.color_underwater1;}
   static void ColorUnderwater1(  WaterMtrlRegion &mr, C Str &t) {mr.edit.color_underwater1=TextVec(t); mr.edit.color_underwater_time.getUTC();}

   static Str  RefractUnderwater(C WaterMtrlRegion &mr          ) {return mr.edit.refract_underwater;}
   static void RefractUnderwater(  WaterMtrlRegion &mr, C Str &t) {mr.edit.refract_underwater=TextFlt(t); mr.edit.refract_underwater_time.getUTC();}

   // #WaterMaterialTextureLayout
   virtual   EditMaterial& getEditMtrl()override  {return edit;}
   virtual C ImagePtr    & getBase0   ()override  {return game->  colorMap();}
   virtual C ImagePtr    & getBase1   ()override  {return game-> normalMap();}
 //virtual C ImagePtr    & getBase2   ()override  {return game->            ;}
 //virtual C ImagePtr    & getDetail  ()override  {return game->detail_map  ;}
 //virtual C ImagePtr    & getMacro   ()override  {return game-> macro_map  ;}
 //virtual C ImagePtr    & getLight   ()override  {return game-> light_map  ;}
   virtual   bool          water      ()C override{return true;}

   void create()
   {
      undos.replaceClass<Change>();
      super.create(); elm_type=ELM_WATER_MTRL; max_zoom=50; preview_cam.dist=15; preview_cam.pitch=-PI_6; preview_cam.setSpherical(); set_mtrl.del(); brightness.del(); preview_mode.del(); preview_big.range=preview.range=200;

      flt e=0.01, prop_height=0.044;
      props.clear();
      props.New().create("Color"                   , MemberDesc(DATA_VEC ).setFunc(Col              , Col              )).setColor();
      props.New().create("Smoothness"              , MemberDesc(DATA_REAL).setFunc(Smooth           , Smooth           )).range(0, 1);
      props.New().create("Reflectivity"            , MemberDesc(DATA_REAL).setFunc(Reflect          , Reflect          )).range(0, 1);
      props.New().create("Normal"                  , MemberDesc(DATA_REAL).setFunc(NrmScale         , NrmScale         )).range(0, 2);
      props.New().create("Flip Normal Y"           , MemberDesc(DATA_BOOL).setFunc(FNY              , FNY              ));
      props.New().create("Vertical Wave Scale"     , MemberDesc(DATA_REAL).setFunc(WaveScale        , WaveScale        )).range(0, 1);

      props.New().create("Scale Color"             , MemberDesc(DATA_REAL).setFunc(ScaleColor       , ScaleColor       )).min(0).mouseEditMode(PROP_MOUSE_EDIT_SCALAR);
      props.New().create("Scale Normal"            , MemberDesc(DATA_REAL).setFunc(ScaleNormal      , ScaleNormal      )).min(0).mouseEditMode(PROP_MOUSE_EDIT_SCALAR);
      props.New().create("Scale Bump"              , MemberDesc(DATA_REAL).setFunc(ScaleBump        , ScaleBump        )).min(5).mouseEditMode(PROP_MOUSE_EDIT_SCALAR);

      props.New().create("Density"                 , MemberDesc(DATA_REAL).setFunc(Density          , Density          )).range(0, 1);
      props.New().create("Density Base"            , MemberDesc(DATA_REAL).setFunc(DensityAdd       , DensityAdd       )).range(0, 1);

      props.New().create("Refraction"              , MemberDesc(DATA_REAL).setFunc(Refract          , Refract          )).range(0, 0.50).mouseEditSpeed(0.25);
      props.New().create("Refraction of Reflection", MemberDesc(DATA_REAL).setFunc(RefractReflection, RefractReflection)).range(0, 0.25).mouseEditSpeed(0.10);

      props.New().create("Underwater Surface Color", MemberDesc(DATA_VEC ).setFunc(ColorUnderwater0 , ColorUnderwater0 )).setColor();
      props.New().create("Underwater Depths Color" , MemberDesc(DATA_VEC ).setFunc(ColorUnderwater1 , ColorUnderwater1 )).setColor();

      props.New().create("Refraction Underwater"   , MemberDesc(DATA_REAL).setFunc(RefractUnderwater, RefractUnderwater)).range(0, 0.04).mouseEditSpeed(0.02);

      Rect prop_rect=AddProperties(props, sub, 0, prop_height, 0.135, &ts); REPAO(props).autoData(this).changed(Changed, PreChanged);

      flt tex_size=prop_height*3; int i=0;
      texs.clear();
      sub+=texs.New().create(TEX_COLOR  , MEMBER(EditWaterMtrl,      color_map), MEMBER(EditWaterMtrl,      color_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Color"         , T); i-=3;
      sub+=texs.New().create(TEX_BUMP   , MEMBER(EditWaterMtrl,       bump_map), MEMBER(EditWaterMtrl,       bump_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Bump"          , T); i-=3;
      sub+=texs.New().create(TEX_NORMAL , MEMBER(EditWaterMtrl,     normal_map), MEMBER(EditWaterMtrl,     normal_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Normal"        , T); i-=3;
    /*sub+=texs.New().create(TEX_RFL_U  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Reflect\nUp"   , T); i-=3;
      sub+=texs.New().create(TEX_RFL_D  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e           , i*prop_height), tex_size, tex_size), "Reflect\nDown" , T); i-=3;
      sub+=texs.New().create(TEX_RFL_ALL, MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*4, i*prop_height), tex_size, tex_size), "Reflect\nAll"  , T);
      sub+=texs.New().create(TEX_RFL_L  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*3, i*prop_height), tex_size, tex_size), "Reflect\nLeft" , T);
      sub+=texs.New().create(TEX_RFL_F  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*2, i*prop_height), tex_size, tex_size), "Reflect\nFront", T);
      sub+=texs.New().create(TEX_RFL_R  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e-tex_size*1, i*prop_height), tex_size, tex_size), "Reflect\nRight", T);
      sub+=texs.New().create(TEX_RFL_B  , MEMBER(EditWaterMtrl, reflection_map), MEMBER(EditWaterMtrl, reflection_map_time), Rect_LU(prop_rect.ru()+Vec2(e+tex_size*0, i*prop_height), tex_size, tex_size), "Reflect\nBack" , T); i-=3; */
      REPA(texs){sub+=texs[i].remove; prop_rect|=texs[i].rect();}

      setBottom(prop_rect);
   }

   // operations
   virtual void flush()override
   {
      if(elm && game && changed)
      {
         if(ElmWaterMtrl *data=elm.waterMtrlData()){data.newVer(); data.from(edit);} // modify just before saving/sending in case we've received data from server after edit
         Save( edit, Proj.editPath(*elm   )); edit.copyTo(*game, Proj);
         Save(*game, Proj.gamePath( elm.id)); Proj.savedGame(*elm);
         Proj.mtrlSetAutoTanBin(elm.id);
         Server.setElmLong(elm.id);
      }
      changed=false;
   }
   virtual void setChanged()override
   {
      if(elm && game)
      {
         changed=true;
         if(ElmWaterMtrl *data=elm.waterMtrlData()){data.newVer(); data.from(edit);}
         edit.copyTo(*game, Proj);
      }
   }
   virtual void set(Elm *elm)override
   {
      if(elm && elm.type!=ELM_WATER_MTRL)elm=null;
      if(T.elm!=elm)
      {
         flush();
         undos.del(); undoVis();
         if(elm)game=     Proj.gamePath( elm.id) ;else game=&temp;
         if(elm)edit.load(Proj.editPath(*elm   ));else edit.reset();
         T.elm   =elm;
         T.elm_id=(elm ? elm.id : UIDZero);
         toGui();
         Proj.refresh(false, false);
         if(!elm)
         {
            MaterialRegion &other=((this==&MtrlEdit) ? WaterMtrlEdit : MtrlEdit);
            hide(); if(other.elm)other.show();
         }
      }
   }

   void set(C WaterMtrlPtr &mtrl) {activate(Proj.findElm(mtrl.id()));}

   virtual void rebuildBase(uint old_base_tex, bool changed_flip_normal_y=false, bool adjust_params=true, bool always=false)override
   {
      if(elm && game)
      {
         uint new_base_tex;
         if(auto_reload || always)
         {
            new_base_tex=Proj.mtrlCreateBaseTextures(edit, changed_flip_normal_y); // set precise
            Time.skipUpdate(); // compressing textures can be slow
         }else new_base_tex=edit.baseTex(); // set approximate

         setChanged();
         if(adjust_params)
         {
            TimeStamp time; time.getUTC();
            uint changed=(old_base_tex^new_base_tex);
            if(changed&BT_BUMP)
            {
               if(!(new_base_tex&BT_BUMP)            )game->wave_scale=0;else
               if(game->wave_scale<=EPS_MATERIAL_BUMP)game->wave_scale=0.1;
            }
            if(changed&(BT_BUMP|BT_NORMAL))
            {
               if(!(new_base_tex&BT_BUMP) && !(new_base_tex&BT_NORMAL))game->normal=0;else
               if(                              game->normal<=EPS_COL8)game->normal=1;
            }
            SyncByValueEqual(edit.wave_scale_time, time, edit.wave_scale, game->wave_scale);
            SyncByValueEqual(edit.    normal_time, time, edit.normal    , game->normal    );
         }
         Proj.mtrlTexChanged();

         toGui();
      }
   }
   virtual void rebuildDetail()override
   {
   }
   virtual void rebuildMacro()override
   {
   }
   virtual void rebuildLight(bool old_light_map, bool adjust_params=true)override
   {
   }

   virtual void elmChanged(C UID &mtrl_id)override
   {
      if(elm && elm.id==mtrl_id)
      {
         undos.set(null, true);
         EditWaterMtrl temp; if(temp.load(Proj.editPath(*elm)))if(edit.sync(temp)){edit.copyTo(*game, Proj); toGui();}
      }
   }
}
WaterMtrlRegion WaterMtrlEdit;
/******************************************************************************/
