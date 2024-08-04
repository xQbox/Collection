
//    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
//    return a.exec();

    /*
     * // qWarning не работает с классом qstring.
     * // Для работы с этим классом нужно перевести его в представление строк на СИ

        int x = 200;
        qWarning() << " Hello, My friend " << x << "Notice that are added ";
        QString msg ("Hello Console!");
        qWarning() << msg << "work!";

        qWarning(msg.toStdString().c_str());


     // Пример работы с QTextStream.
      // Объект QTextStream позволяет выбирать поток вывода (stdout , stderr, ?)
    QTextStream out_stream(stdout);
    out_stream.setFieldWidth(10);
    out_stream.setPadChar('*');
    out_stream << msg << x << '\n';
     Пример работы с Qstring и QObject

    QCoreApplication a(argc, argv);

    QString early_msg(QObject::tr("Thats my life!"));
    QTranslator translator;

    QTextStream out_stream(stdout);

    bool result = translator.load("trans_es");

    if (!result)
        out_stream << "Error: failed to load the translation \n";
    else
        a.installTranslator(&translator);

    QString msg = QObject::tr("Hello");
    QString msg2 (QObject::tr("Googbye"));

    out_stream << early_msg << '\n';
    out_stream << msg << '\n' << msg2 << endl;

    return a.exec();
    */
