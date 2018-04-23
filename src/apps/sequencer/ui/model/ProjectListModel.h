#pragma once

#include "Config.h"

#include "ParamListModel.h"

#include "model/Project.h"

class ProjectListModel : public ParamListModel {
public:
    ProjectListModel(Project &project) :
        _project(project)
    {}

    virtual int rows() const override {
        return Last;
    }

    virtual int columns() const override {
        return 2;
    }

    virtual void cell(int row, int column, StringBuilder &str) const override {
        if (column == 0) {
            formatName(Item(row), str);
        } else if (column == 1) {
            formatValue(Item(row), str);
        }
    }

    virtual void edit(int row, int column, int value, bool shift) override {
        if (column == 1) {
            editValue(Item(row), value, shift);
        }
    }

    virtual Routing::Param routingParam(int row) const override {
        switch (Item(row)) {
        case Bpm:
            return Routing::Param::Bpm;
        case Swing:
            return Routing::Param::Swing;
        default:
            return Routing::Param::None;
        }
    }

private:
    enum Item {
        Name,
        Bpm,
        Swing,
        SyncMeasure,
        Scale,
        RootNote,
        Last
    };

    static const char *itemName(Item item) {
        switch (item) {
        case Name:              return "Name";
        case Bpm:               return "BPM";
        case Swing:             return "Swing";
        case SyncMeasure:       return "Sync Measure";
        case Scale:             return "Scale";
        case RootNote:          return "Root Note";
        case Last:              break;
        }
        return nullptr;
    }

    void formatName(Item item, StringBuilder &str) const {
        str(itemName(item));
    }

    void formatValue(Item item, StringBuilder &str) const {
        switch (item) {
        case Name:
            str(_project.name());
            break;
        case Bpm:
            _project.printBpm(str);
            break;
        case Swing:
            _project.printSwing(str);
            break;
        case SyncMeasure:
            _project.printSyncMeasure(str);
            break;
        case Scale:
            _project.printScale(str);
            break;
        case RootNote:
            _project.printRootNote(str);
        case Last:
            break;
        }
    }

    void editValue(Item item, int value, bool shift) {
        switch (item) {
        case Name:
            break;
        case Bpm:
            _project.editBpm(value, shift);
            break;
        case Swing:
            _project.editSwing(value, shift);
            break;
        case SyncMeasure:
            _project.editSyncMeasure(value, shift);
            break;
        case Scale:
            _project.editScale(value, shift);
            break;
        case RootNote:
            _project.editRootNote(value, shift);
            break;
        case Last:
            break;
        }
    }

    Project &_project;
};
