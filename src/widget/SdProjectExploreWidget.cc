#include "widget/SdProjectExploreWidget.h"


SdProjectExploreWidget::SdProjectExploreWidget()
{
    QTreeWidgetItem* item=new QTreeWidgetItem();
    item->setText(0,"Faeris.fsprite2");

    addTopLevelItem(item);

    setHeaderHidden(true);
}

SdProjectExploreWidget::~SdProjectExploreWidget()
{
}


