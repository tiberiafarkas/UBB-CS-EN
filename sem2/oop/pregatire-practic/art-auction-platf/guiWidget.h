#include <QtWidgets/QWidget>    
#include "service.h"  
#include "ui_guiWidget.h"

//QT_BEGIN_NAMESPACE  
//namespace Ui { class guiWidget; }  
//QT_END_NAMESPACE  

class guiWidget : public QWidget, public Observer {  
   Q_OBJECT  

public:  
   guiWidget(Service& service, User user);  
   ~guiWidget() override;  
   void update() override;  

private:  
   Ui::guiWidgetClass ui; 
   Service& service;  
   User user;  
   bool isAdministrator;

public slots:  
   void comboBoxChanged();  
   void addButtonClicked();  
   void populateList();  
   void bidUser();  
   void showOffers();
};
