

#ifndef __NGX_CONF_H__
#define __NGX_CONF_H__

#include <vector>

#include "ngx_global.h"

class CConfig
{
private:
    static CConfig* m_instance;
    
public:
    CConfig();
    ~CConfig();

    static CConfig* GetInstance()
    {
        if(!m_instance)
            m_instance = new CConfig();
        return m_instance;
    };

    bool Load(const char *pconfName);
    const char *GetString(const char *p_itemname);
    int GetIntDefault(const char *p_itemname, const int def);
    
	std::vector<LPCConfItem> m_ConfigItemList; //存储配置信息的列表
};

#endif