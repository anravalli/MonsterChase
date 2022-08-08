/*
 * optionpage_view.cpp
 *
 *  Created on: 28 mar 2022
 *      Author: andrea
 */

#include "hiscorepage_view.h"
#include <ui_framework/uiviewitems_qt.h>
#include <ui_framework/uipagemenuwidgets_qt.h>

#include <gameconfig.h>

#define TABLE_ROW_NUM 11
#define TABLE_FONT_SIZE 14
#define TABLE_ROW_SPACING 25
#define TABLE_FONT_COLOR 0xaa,0x00,0x00
#define TABLE_FONT_BORDER_COLOR 0xa1,0x97,0xc1

HiscorePageView::HiscorePageView(UiPageViewQt *parent):
	UiPageViewQt(parent)
{
	/*
	 * page structure:
	 * * logo: QGraphicsPixmapItem
	 * * match type selector: UiMenuItemMultiValWidget_qt
	 * * hight score table: HighScoreTable_qt
	 * * exit button: UiMenuItemWidget_qt
	 */
	double pw_center = GameConfig::playground_width/2;

	auto logo = new QGraphicsPixmapItem(QPixmap(":/resources/monster_chase_logo.png"));
	logo->setScale(0.5);

	vector<QString> hiscore_tables = {"hunter",	"survivor", "the dark hunt", "alone in the dark"};
	table_selector = new UiMenuItemMultiValWidget_qt(hiscore_tables);
	table_selector->set_current(0);
	table_selector->setPos(pw_center-table_selector->width()/2,
			logo->boundingRect().height()/2);
	table_selector->set_font_size(18);

	double table_x = pw_center - 500/2;
	double table_y = logo->boundingRect().height()/2+(table_selector->height()*2);
	double table_h = TABLE_ROW_NUM * (TABLE_ROW_SPACING+TABLE_FONT_SIZE);
	hiscore_table = new HighScoreTable_qt(table_x,table_y, 500, table_h);

	exit_button = new UiMenuItemWidget_qt("Back");
	exit_button->setPos(pw_center-exit_button->width()/2, table_y+table_h+TABLE_ROW_SPACING);

	QPointF exit_highlight_pos(pw_center-exit_button->width()/2, table_y+table_h+TABLE_ROW_SPACING);
	exit_highlight = new UiPageMenuItemSelectioBoxWidget_qt(exit_highlight_pos,
			exit_button->width(), exit_button->height());

	scene->addItem(logo);
	table_selector->addToPage(this);
	hiscore_table->addToScene(scene);
	exit_highlight->addToPage(this);
	exit_button->addToPage(this);

	exit_highlight->hide();
}

HiscorePageView::~HiscorePageView()
{
	// TODO Auto-generated destructor stub
}

void HiscorePageView::setUpView()
{
    view->setBackgroundBrush(QColor(0xff, 0x68, 0x16, 0xff));
    //view->setBackgroundBrush(QColor(0x8e,0x68,0x85,0xff));
}


void HiscorePageView::update_score_table(vector<vector<QString> > *data)
{
	hiscore_table->update(data);
}

int HiscorePageView::next_table()
{
	table_selector->next();
	int next_idx = table_selector->get_current();
	table_selector->moveBy(GameConfig::playground_width/2-table_selector->center_anchor().x(),0);
	//qDebug("HiscorePageView: current table: %d", next_idx);
	return next_idx;
}

int HiscorePageView::previous_table()
{
	table_selector->previous();
	int prev_idx = table_selector->get_current();
	table_selector->moveBy(GameConfig::playground_width/2-table_selector->center_anchor().x(),0);
	//qDebug("HiscorePageView: current table: %d", prev_idx);
	return prev_idx;

}

void HiscorePageView::activate_exit_button(bool active)
{
	if(active)
		exit_highlight->show();
	else
		exit_highlight->hide();
}
/*
 * HighScoreTable_qt definitions
 */

class HighScoreTableLabel_qt: public QGraphicsSimpleTextItem
{
public:
	HighScoreTableLabel_qt(QString text, int font_size, QColor color, QFont::Weight style): QGraphicsSimpleTextItem(text)
	{
		QFont font("Helvetica",font_size,style);
		this->setFont(font);
		this->setPen(QPen(QColor(color)));
		this->setBrush(QBrush(color));
	}
};

HighScoreTable_qt::HighScoreTable_qt(double _x, double _y, double _w, double _h):
		x(_x), y(_y), w(_w), h(_h)
{
	/*
	 * * hight score table:  top 10 score with header (player name, play time, score)
	 */
	labels = new vector<vector<HighScoreTableLabel_qt *> *>();

	vector<QString> header_label = {"Player", "Time", "Score"};
	vector<HighScoreTableLabel_qt *> *header = new vector<HighScoreTableLabel_qt *>();
	double col_spacing = w/3;
	double row_spacing = (h/*-TABLE_ROW_SPACING*/)/TABLE_ROW_NUM;

	for(unsigned int col_idx=0; col_idx<header_label.size(); col_idx++)
	{
		auto l = header_label[col_idx];
		HighScoreTableLabel_qt *label = new HighScoreTableLabel_qt(l, TABLE_FONT_SIZE, QColor(TABLE_FONT_COLOR), QFont::Bold);
		label->setPos(x+col_spacing*col_idx+20, y+5);
		header->push_back(label);
	}
	labels->push_back(header);
	for(int i=1; i<TABLE_ROW_NUM; i++)
	{
		vector<HighScoreTableLabel_qt *> *row = new vector<HighScoreTableLabel_qt *>();
		for(int j=0; j<3; j++)
		{
			HighScoreTableLabel_qt *label = new HighScoreTableLabel_qt("<empty>", TABLE_FONT_SIZE, QColor(TABLE_FONT_COLOR), QFont::Normal);
			label->setPos(x+col_spacing*j+20, y+row_spacing*i+5);
			row->push_back(label);
		}
		labels->push_back(row);
	}
}

HighScoreTable_qt::~HighScoreTable_qt()
{
	for(auto r: *labels)
	{
		for(auto i: *r)
		{
			delete i;
		}
		delete r;
	}
	delete labels;
}

void HighScoreTable_qt::addToScene(QGraphicsScene *scene)
{
	scene->addItem(this);
	for(auto r: *labels)
	{
		for(auto i: *r)
		{
			scene->addItem(i);
		}
	}
}

void HighScoreTable_qt::update(vector<vector<QString>> *model)
{
	for(unsigned int i=1; i< labels->size(); i++)
	{
		vector<HighScoreTableLabel_qt *> *row = (*labels)[i];
		vector<QString> new_row_labels = (*model)[i-1];
		for(unsigned int j=0; j< row->size(); j++)
		{
			(*row)[j]->setText(new_row_labels[j]);
		}
	}
}

QRectF HighScoreTable_qt::boundingRect() const
{
	return QRectF(x,y,w,h);
}

void HighScoreTable_qt::paint(QPainter *painter,
		const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);
	double col_spacing = w/3;
	double row_spacing = (h/*-TABLE_ROW_SPACING*/)/TABLE_ROW_NUM;

	painter->setPen(Qt::NoPen);
	painter->setBrush(QColor(0xff,0xd1,0x2a));
	painter->drawRect(x, y, w, row_spacing);

	painter->setPen(QPen(Qt::black, 2));
	painter->setBrush(Qt::NoBrush);
	painter->drawRect(x, y, w, h);

	for(int i=0; i<=TABLE_ROW_NUM; i++)
		painter->drawLine(x, y+row_spacing*i, x+w, y+row_spacing*i);
	for(int j=0; j<3; j++)
		painter->drawLine(x+col_spacing*j, y, x+col_spacing*j, y+h);
}

void HighScoreTable_qt::setPos(double x, double y)
{
	this->x = x;
	this->y = y;
}

void HighScoreTable_qt::resize(double w, double h)
{
	this->w = w;
	this->h = h;
}
