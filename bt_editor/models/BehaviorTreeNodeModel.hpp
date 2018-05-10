#pragma once

#include <QObject>
#include <QLabel>
#include <QFormLayout>
#include <QComboBox>

#include <nodes/NodeDataModel>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <functional>

using QtNodes::PortType;
using QtNodes::PortIndex;
using QtNodes::NodeData;
using QtNodes::NodeDataType;
using QtNodes::NodeDataModel;

struct ParameterWidgetCreator{
    QString label;
    std::function<QWidget*(QWidget*)> instance_factory;
};

typedef std::vector<ParameterWidgetCreator> ParameterWidgetCreators;


class BehaviorTreeNodeModel : public NodeDataModel
{
    Q_OBJECT

public:
  BehaviorTreeNodeModel(const QString &registration_name,
                        const QString &instance_name,
                        const ParameterWidgetCreators &parameters );

  virtual ~BehaviorTreeNodeModel() {}

  virtual bool captionVisible() const override final
  { return false; }

public:

  NodeDataType dataType(PortType , PortIndex ) const override final;

  virtual std::shared_ptr<NodeData> outData(PortIndex port) override final;

  void setInData(std::shared_ptr<NodeData>, int) override final {}

  virtual QString caption() const override final;

  const QString& registrationName() const;

  QString name() const override final { return registrationName(); }

  const QString& instanceName() const;
  virtual void setInstanceName(const QString& name);

  std::vector<std::pair<QString, QString> > getCurrentParameters() const;

  virtual QWidget *embeddedWidget() override final { return _main_widget; }

  virtual QJsonObject save() const override;

  virtual void restore(QJsonObject const &) override;

  virtual void lock(bool locked) final;


protected:
  QWidget*   _main_widget;
  QWidget*   _params_widget;
  QFormLayout *_form_layout;
  QLabel*    _label_ID;
  QLineEdit* _line_edit_name;
private:
  const QString _registration_name;
  QString _instance_name;

signals:
  void adjustSize();
};
