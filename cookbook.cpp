#include "cookbook.h"

CookBook::CookBook(QWidget *parent, DatabaseHandler *_dbHandler)
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed
    dbHandler = _dbHandler;
    setFixedSize(700, 500);

    QPushButton *backBtn = new QPushButton("Back", this);
    connect(backBtn, &QPushButton::clicked, this, [this]{
        emit cookBookClosed();
        close();
    });

    QLabel *header = new QLabel("My Cookbook", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);


    proposeDish = new QPushButton("Propose Dish", this);

    createShoppingList = new QPushButton("Create Shopping List", this);

    QHBoxLayout *buttons = new QHBoxLayout;
    buttons->setSizeConstraint(QLayout::SetMinimumSize);
    buttons->addWidget(proposeDish);
    buttons->addWidget(createShoppingList);

    addRecipe = new QPushButton("Add recipe", this);
    connect(addRecipe, SIGNAL (clicked(bool)), this, SLOT (openRecipeEdit()));

    QWidget *widget = new QWidget(this);
    recipesScroll = new QScrollArea(this);
    recipesScroll->setWidgetResizable( true );
    recipes = new QVBoxLayout(widget);
    recipes->setSizeConstraint(QLayout::SetMinimumSize);
    widget->setLayout(recipes);
    recipesScroll->setWidget(widget);


    vstack = new QVBoxLayout(this);
    vstack->setSizeConstraint(QLayout::SetMinimumSize);
    vstack->addWidget(backBtn);
    vstack->addWidget(header);
    vstack->addLayout(buttons);
    vstack->addWidget(addRecipe);
    vstack->addWidget(recipesScroll);

    dbHandler->downloadFromDatabase(QString("cookbook"));
    connect(dbHandler, SIGNAL (downloadDone()), this, SLOT (updateRecipes()));
}

void CookBook::openRecipeEdit(const QString &id)
{
    hide();
    RecipeEditComponent *edit = new RecipeEditComponent(nullptr, dbHandler, id);
    edit->show();
    connect(edit, SIGNAL (recipeEditClosed()), this, SLOT (show()));
}

void CookBook::updateRecipes()
{
    QLayoutItem *child;
    while ((child = recipes->takeAt(0)) != 0) {
      delete child->widget();
    }

    QJsonObject json = dbHandler->cookbook.object();
    for (const QString &key: json.keys()) {
        QJsonObject obj = json.value(key).toObject();

        QString name = obj["Name"].toString();

        QPushButton *editBtn = new QPushButton("Edit", this);
        connect(editBtn, &QPushButton::clicked, this, [this, key]{openRecipeEdit(key);});

        // delete button deletes wokroutPlan from DB
        QPushButton *deleteBtn = new QPushButton("Delete", this);
        connect(deleteBtn, &QPushButton::clicked, dbHandler, [this,key]{dbHandler->deleteEntry("cookbook", key);});

        QHBoxLayout *buttons = new QHBoxLayout;
        buttons->addWidget(editBtn);
        buttons->addWidget(deleteBtn);

        QVBoxLayout *vbox = new QVBoxLayout(this);
        vbox->setSizeConstraint(QLayout::SetMinimumSize);


        vbox->addWidget(new QLabel("Instructions: " + obj["Instructions"].toString(), this));

        QJsonArray ingredients = obj["Ingredients"].toArray();
        for(const auto & ing: ingredients) {
            QJsonObject ingredientData = ing.toObject();


            QWidget *widget = new QWidget(this);
            QHBoxLayout *ingredientView = new QHBoxLayout(widget);
            ingredientView->addWidget(new QLabel("Name:" + ingredientData["Name"].toString(), this));
            ingredientView->addWidget(new QLabel("Amount:" + ingredientData["Amount"].toString(), this));

            widget->setLayout(ingredientView);
            vbox->addWidget(widget);
        }
        vbox->addLayout(buttons);

        QGroupBox *gBox = new QGroupBox(name,this);
        gBox->setLayout(vbox);
        gBox->setMinimumSize(600, 150);

        recipes->addWidget(gBox, 0, Qt::AlignTop);
    }
}
