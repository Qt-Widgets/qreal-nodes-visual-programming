#pragma once

#include "../../../qrutils/generator/abstractGenerator.h"

namespace generators {
namespace generator {

class MyAbstractGenerator : public utils::AbstractGenerator
{
public:
	/** Constructor.
	  @param templateDirPath Path to a directory with generation template.
	  @param outputDirPath Path to a directory.
	  @param logicalModel Logical model reference.
	  @param errorReporter Object to return errors to.
	  */
	MyAbstractGenerator(QString const &templateDirPath
			, QString const &outputDirPath
			, QString const &pathToQReal
			, qReal::LogicalModelAssistInterface const &logicalModel
			, qReal::ErrorReporterInterface &errorReporter
			, QString const &metamodelLanguageName
			, QString const &languageName
			, QString const &nodeName
			, QString const &toGeneratePropertyName
			, QString const &programNamePropertyName
			, QString const &generatorMetamodelName
			);

	virtual ~MyAbstractGenerator();

	/// Starts generation.
	void generate() = 0;

	QString modelFullName();
	QString metamodelName();
	QString languageName();
	QString generatorModelName();//i.e. pluginName
	QString normalizerMetamodelName();
	QString normalizerLanguageName();
	QString normalizerGeneratorModelName();//i.e. normalizerPluginName
	QString normalizerGeneratorClassModelName();

protected :

	void generateTemplate(qReal::Id const &element);
	void generateTemplateUsingTextCode(qReal::Id const &element, QString const& textCode);
	void saveTemplateUtils();
	QString generateTemplateConstStringNames();

	QString mPathToQReal;
	QString const &mMetamodelName;//имя метамодели языков, для которых напсана эта модель генератора, по которой генерируется код
	QString const &mLanguageName; //имя конкретного языка метамодели, для которого напсана эта модель генератора
	QString const &mNodeName; //имя главного узла языка (который является "корнем" программы)
	QString const &mToGeneratePropertyName;//имя свойства главного узла языка, в котором указывается путь до папки генерации программы
	QString const &mProgramNamePropertyName; //имя свойства главного узла языка, в котором указывается имя генерируемой программы
	QString const &mGeneratorName;//настоящее имя модели генератора, по которой генерируется код

	QMap<QString, QString> mMarksCode; // соответсвие меток и кода, которое будет использовать сгенерённый генератор
	QMap<QString, QString> mTemplateVariableFilename; // соответствие имен переменных и имен файлов-шаблонов, которые будет использовать сгенерённый генератор
	QString const mTemplateDirName; // имя папки шаблонов для этого генератора
};

}
}
