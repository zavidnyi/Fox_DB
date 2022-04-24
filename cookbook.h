#ifndef COOKBOOK_H
#define COOKBOOK_H

#include <QWidget>
#include "databasehandler.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include "recipeeditcomponent.h"
#include <QJsonObject>
#include <QGroupBox>
#include <QJsonArray>
#include <QInputDialog>
#include <QSet>
#include <QMap>
#include <QMessageBox>

class CookBook : public QWidget
{
    Q_OBJECT
public:
    explicit CookBook(QWidget *parent = nullptr, DatabaseHandler *_dbHandler = nullptr);
private:
    DatabaseHandler *dbHandler;
    QVBoxLayout *vstack;
    QPushButton *proposeDish;
    QPushButton *createShoppingList;
    QPushButton *addRecipe;
    QScrollArea *recipesScroll;
    QVBoxLayout *recipes;
    QMap<QString, QSet<QString> > dishToIngredients;
private slots:
    void openRecipeEdit(const QString &id = "");
    void updateRecipes();
    void openDishProposalDialog();
signals:
    void cookBookClosed();
};

#endif // COOKBOOK_H
