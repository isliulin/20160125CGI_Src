#include "CGI_SCADA_DLL_TreeItemOperating_status.h"
#include "../CGI_SCADA_include/CGI_SCADA_define.h"


CGI_SCADA_DLL_TreeItemOperating_status::CGI_SCADA_DLL_TreeItemOperating_status(QTreeWidgetItem *parentTreeItem_, const QStringList &strings, int type, QObject *parent):
    CGI_SCADA_DLL_TreeItemBase(parentTreeItem_,strings,type,parent)
{
//    m_pWidget = NULL;
    m_pMainView = new QWebView;
    m_pCookieJar = new QNetworkCookieJar();
    m_pMainView->page()->networkAccessManager()->setCookieJar(m_pCookieJar);
    m_bIP_CookieIsInit = false;
}

CGI_SCADA_DLL_TreeItemOperating_status::~CGI_SCADA_DLL_TreeItemOperating_status()
{
    if (m_pMainView != NULL)
    {
        m_pMainView->deleteLater();
        m_pMainView = NULL;
    }
    if (m_pCookieJar != NULL)
    {
        m_pCookieJar->deleteLater();
        m_pCookieJar = NULL;
    }
}

QWidget *CGI_SCADA_DLL_TreeItemOperating_status::GetWidget(QTreeWidgetItem */*pItem_*/)
{
    if (!m_bIP_CookieIsInit)
    {
        QList<QNetworkCookie> cookies;
        cookies.append(QNetworkCookie("key1", CGI_SCADA_define::s_baCookie));
        qDebug()<<__func__<<__LINE__<<CGI_SCADA_define::s_strIPAddress<<CGI_SCADA_define::s_baCookie;
        m_pCookieJar->setCookiesFromUrl(cookies, QString(URL_TreeItemType_DeviceM_operating_status).arg(CGI_SCADA_define::s_strIPAddress));
        m_bIP_CookieIsInit = true;
    }
    m_pMainView->load(QUrl(QString(URL_TreeItemType_DeviceM_operating_status).arg(CGI_SCADA_define::s_strIPAddress)));
    return m_pMainView;
}
