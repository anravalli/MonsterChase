/*
 * optionpage_view.h
 *
 *  Created on: 28 mar 2022
 *      Author: andrea
 */

#ifndef SRC_HISCORE_PANEL_OPTIONPAGE_VIEW_H_
#define SRC_HISCORE_PANEL_OPTIONPAGE_VIEW_H_

#include <QtWidgets>
#include <QGraphicsItem>
#include <vector>
#include <ui_framework/uipageview_qt.h>

using namespace std;
//same as MonsterChaseMainPage
//* implement PageView with custom color
//* host graphics like game logo
//* host menu items via inherited addItem() method

class UiMenuItemMultiValWidget_qt;
class UiMenuItemWidget_qt;
class UiPageMenuItemSelectioBoxWidget_qt;
class HighScoreTableLabel_qt;

class HighScoreTable_qt: public QGraphicsItem
{
public:
	HighScoreTable_qt(double x, double y, double w, double h);
	~HighScoreTable_qt();

	void update(vector<vector<QString>> *model);

	QRectF boundingRect() const Q_DECL_OVERRIDE;

	void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

	void setPos(double x, double y);
	void resize(double w, double h);
	void addToScene(QGraphicsScene *scene);

private:
    double x;
    double y;
    double w;
    double h;
    int rows;
    int cols;
	vector<vector<HighScoreTableLabel_qt *> *> *labels;
};

class HiscorePageView: public UiPageViewQt {
public:
	HiscorePageView(UiPageViewQt *parent);
	virtual ~HiscorePageView();

protected:
    virtual void setUpView() override;
public:
    void update_score_table(vector<vector<QString>> *data);
    int next_table();
    int previous_table();
    void activate_exit_button(bool active);
private:
    UiMenuItemMultiValWidget_qt *table_selector = nullptr;
    UiMenuItemWidget_qt *exit_button = nullptr;
    UiPageMenuItemSelectioBoxWidget_qt *exit_highlight = nullptr;
    HighScoreTable_qt *hiscore_table = nullptr;
};

#endif /* SRC_HISCORE_PANEL_OPTIONPAGE_VIEW_H_ */
