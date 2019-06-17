/******************************************************************************/
class ProjectUpdate
{
   Memc<UID> texs;
   Project  *proj=null;
   SyncLock  lock;

   static void Error    (C Str &error) {Gui.msgBox(S, error);}
   static void ErrorLoad(C Str &path ) {Error(S+"Can't load image:\n\""+path+'"');}
   static void ErrorSave(C Str &path ) {Error(S+"Can't save image:\n\""+path+'"');}
   static void UpdateTex(  UID &tex_id, ProjectUpdate &pu, int thread_index) {pu.updateTex(tex_id);}
          void updateTex(C UID &tex_id)
   {
      Str   path=proj.texPath(tex_id);
      Image img;

      // load
      File f, temp, *src=&f;

      if(!f.readTry(path)){ErrorLoad(path); goto error;}
      if(IsServer)
      {
         if(!Decompress(*src, temp, true)){ErrorLoad(path); goto error;}
         src=&temp; src.pos(0);
      }
      ThreadMayUseGPUData();
      if(!img.load(*src)){ErrorLoad(path); goto error;}
      f.del();

      // convert
      if(!UpdateMtrlBase1Tex(img, img)){Error("Can't convert texture"); goto error;}

      // save
      if(IsServer) // server
      {
         if(!img.save(temp.writeMem())){ErrorSave(path); goto error;} temp.pos(0);
         if(!Compress(temp, f.writeMem(), COMPRESS_LZMA, 5, false)){ErrorSave(path); goto error;} f.pos(0);
         if(!SafeOverwrite(f, path)){ErrorSave(path); goto error;}
      }else
      if(!Save(img, path)){ErrorSave(path); goto error;} // client

      {
         SyncLocker locker(lock);
         proj.texs_update.binaryExclude(tex_id, Compare);
      }
      error:;
   }
   void start(Project &proj, Threads &threads)
   {
      T.proj=&proj;
      T.texs=proj.texs_update; // copy because 'proj.texs_update' will be dynamically updated
      REPA(texs)threads.queue(texs[i], UpdateTex, T);
   }
   void stop(Threads &threads)
   {
      REPA(texs)threads.cancel(texs[i], UpdateTex, T);
      REPA(texs)threads.wait  (texs[i], UpdateTex, T);
      T.proj=null;
   }
}
/******************************************************************************/
