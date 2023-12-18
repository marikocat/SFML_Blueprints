
namespace orm
{
    class SlqObjectBase;

    template<typename T>
    Register<T>::Register()
    {
        std::cerr<<"at Register start _create number "<<Tables::_create.size()<<std::endl;
        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_MAGENTA<<"[Register] Table "<<SqlObject<T>::_table<<ORM_COLOUR_NONE<<std::endl;
        #endif

        static typename T::pointer tmp = T::create();
        for(VAttr* attr: static_cast<SqlObject<T>*>(tmp.get())->_attributsVector)
        {
            #if ORM_DEBUG & ORM_DEBUG_REGISTER
            //std::cerr<<ORM_COLOUR_MAGENTA<<"[Register] Attr "<<attr->_column<<ORM_COLOUR_NONE<<std::endl;
            #endif
            SqlObject<T>::_staticAttributsVector.emplace_back(attr);
        }
        for(VFK* fk: static_cast<SqlObject<T>*>(tmp.get())->_fkAttributsVector)
        {
            #if ORM_DEBUG & ORM_DEBUG_REGISTER
            //std::cerr<<ORM_COLOUR_MAGENTA<<"[Register] Fk "<<fk->_column<<ORM_COLOUR_NONE<<std::endl;
            #endif
            SqlObject<T>::_staticFksAttributsVector.emplace_back(fk);
        }

        Tables::getFactory().add(SqlObject<T>::_table, [](){
            return std::dynamic_pointer_cast<SqlObjectBase>(T::create());
        });

        Tables::_create.push_back(
                                 []()->bool{
                                    return SqlObject<T>::createTable();
                                 }
                                );

        Tables::_drop.push_back(
                               []()->bool{
                                return SqlObject<T>::dropTable();
                                }
                            );

        Tables::_clear.push_back(
                                   []()->bool{
                                    return SqlObject<T>::clearTable();
                                    }
                                );

        #if ORM_DEBUG & ORM_DEBUG_REGISTER
        std::cerr<<ORM_COLOUR_MAGENTA<<"[Register] END Table "<<SqlObject<T>::_table<<ORM_COLOUR_NONE<<std::endl;
        #endif
        std::cerr<<"at Register end _create number "<<Tables::_create.size()<<std::endl;
    }
}
