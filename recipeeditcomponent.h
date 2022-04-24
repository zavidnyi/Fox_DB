#ifndef RECIPEEDITCOMPONENT_H
#define RECIPEEDITCOMPONENT_H

#include <QWidget>
#include "databasehandler.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPlainTextEdit>
#include <QFontMetrics>
#include <QScrollArea>
#include <QInputDialog>
#include <QVariantMap>
#include <QJsonObject>
#include <QJsonArray>

class RecipeEditComponent : public QWidget
{
    Q_OBJECT
public:
    explicit RecipeEditComponent(QWidget *parent = nullptr, DatabaseHandler *_dbHandler = nullptr, const QString &curId = "");
private:
    DatabaseHandler *dbHandler;
    QVBoxLayout *vstack;
    QString id;
    QPlainTextEdit *name;
    QPlainTextEdit *instructions;
    QPushButton *addIngredient;
    QPushButton *saveBtn;
    QScrollArea *ingredientsScroll;
    QVBoxLayout *ingredients;
    QVariantMap ingredientsMap;
signals:
    void recipeEditClosed();
private slots:
    void openIngredientDialog();
    void updateIngredients();
    void saveRecipe();
};

#endif // RECIPEEDITCOMPONENT_H
