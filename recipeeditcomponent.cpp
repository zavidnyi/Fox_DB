#include "recipeeditcomponent.h"

RecipeEditComponent::RecipeEditComponent(QWidget *parent,  DatabaseHandler *_dbHandler, const QString &curId)
    : QWidget{parent}
{
    setAttribute( Qt::WA_DeleteOnClose, true ); // Widget will be deleted automatically when closed
    dbHandler = _dbHandler;
    id = curId;
    setFixedSize(700, 500);

    QPushButton *backBtn = new QPushButton("Back", this);
    connect(backBtn, &QPushButton::clicked, this, [this]{
        emit recipeEditClosed();
        close();
    });

    QLabel *header = new QLabel("Edit Recipe", this);
    header->setFont(QFont("lucida", 24, QFont::Bold, false));
    header->setAlignment(Qt::AlignCenter);


    name = new QPlainTextEdit(this);
    QFontMetrics m (name -> font());
    int RowHeight = m.lineSpacing();
    name->setFixedHeight(1* RowHeight + 8); // Title text field height is set to one line, 8 is margin

    instructions = new QPlainTextEdit(this);
    instructions->setFixedHeight(100);

    // widget overhead is neccessary to make it scrollable
    QWidget *widget = new QWidget(this);
    ingredientsScroll = new QScrollArea(this);
    ingredientsScroll->setWidgetResizable( true );
    ingredients= new QVBoxLayout(widget);
    widget->setLayout(ingredients);
    ingredientsScroll->setWidget(widget);

    addIngredient = new QPushButton("Add ingredient", this);
    connect(addIngredient, SIGNAL (clicked(bool)), this, SLOT (openIngredientDialog()));

    saveBtn = new QPushButton("Save", this);
    connect(saveBtn, SIGNAL (clicked(bool)), this, SLOT (saveRecipe()));

    if (!id.isEmpty()) {
        QJsonObject data = dbHandler->cookbook.object()[id].toObject();

        name->setPlainText(data["Name"].toString());
        instructions->setPlainText(data["Instructions"].toString());
        for (const auto & ing: data["Ingredients"].toArray()) {
            ingredientsMap[QString::number(ingredientsMap.size())] = ing.toVariant();
        }
        qDebug() << ingredientsMap;
    }


    vstack = new QVBoxLayout(this);
    vstack->addWidget(backBtn);
    vstack->addWidget(header);
    vstack->addWidget(new QLabel("Name of recipe:"));
    vstack->addWidget(name);
    vstack->addWidget(new QLabel("Instructions:"));
    vstack->addWidget(instructions);
    vstack->addWidget(ingredientsScroll);
    vstack->addWidget(addIngredient);
    vstack->addWidget(saveBtn);
    updateIngredients();
}

void RecipeEditComponent::openIngredientDialog()
{
    bool ok;
    QString name = QInputDialog::getText(this, tr("Adding Ingredient"),
                                         tr("Ingredient Name:"), QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.isEmpty()) return;

    QString amount = QInputDialog::getText(this, tr("Adding Ingredient"),
                                         tr("Amount:"), QLineEdit::Normal,
                                         "", &ok);
    if (!ok || name.isEmpty()) return;

    QVariantMap ingredient;
    ingredient["Name"] = name;
    ingredient["Amount"] =amount;
    ingredientsMap[QString::number(ingredientsMap.size())] = ingredient;
    updateIngredients();
}

void RecipeEditComponent::updateIngredients()
{
    QLayoutItem *child;
    while ((child = ingredients->takeAt(0)) != 0) {
      delete child->widget();
    }

    for (QVariantMap::const_iterator iter = ingredientsMap.cbegin(); iter != ingredientsMap.cend(); ++iter) {
        QVariantMap ingredientData = iter.value().toMap();


        QWidget *widget = new QWidget(this);
        QHBoxLayout *ingredientView = new QHBoxLayout(widget);
        ingredientView->addWidget(new QLabel("Name:" + ingredientData["Name"].toString(), this));
        ingredientView->addWidget(new QLabel("Amount:" + ingredientData["Amount"].toString(), this));
        QPushButton *deleteBtn = new QPushButton("Delete",this);
        connect(deleteBtn, &QPushButton::clicked, this, [this, iter]{
            ingredientsMap.erase(iter);
            updateIngredients();
        });
        ingredientView->addWidget(deleteBtn);
        widget->setLayout(ingredientView);

        ingredients->addWidget(widget);
    }
}

void RecipeEditComponent::saveRecipe()
{
    QVariantMap data;
    data["Name"] = name->toPlainText();
    data["Instructions"] = instructions->toPlainText();
    data["Ingredients"] = ingredientsMap;
    if (id.isEmpty())
        dbHandler->uploadToDatabase(QJsonDocument::fromVariant(data), "cookbook");
    else
        dbHandler->updateEntry(QJsonDocument::fromVariant(data), "cookbook", id);
}


