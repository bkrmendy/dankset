#include "Set.h"

#include "gtest/gtest.h"
#include "rapidcheck.h"
#include "rapidcheck/gtest.h"
#include "rapidcheck/state.h"

#include <set>

struct SetModel {
    std::set<int> data;
};

using IntSet = Set<int>;


struct Insert : rc::state::Command<SetModel, IntSet>{
    int key;
    void apply(Model &s0) const override {
        s0.data.insert(key);
    }

    void run(const Model &s0, Sut &sut) const override {
        sut.insert(key);
        RC_ASSERT(sut.contains(key));
        RC_ASSERT(sut.size() == s0.data.size());
    }

    void show(std::ostream &os) const override {
        os << "Insert " << key;
    }
};

struct Erase : rc::state::Command<SetModel, IntSet> {
    int key;
    void checkPreconditions(const Model &s0) const override {
        RC_PRE(s0.data.count(key) > 0);
    }

    void apply(Model &s0) const override {
        s0.data.erase(key);
    }

    void run(const Model &s0, Sut &sut) const override {
        sut.insert(key);
        RC_ASSERT(not sut.contains(key));
        RC_ASSERT(sut.size() == s0.data.size());
    }

    void show(std::ostream &os) const override {
        os << "Erase " << key;
    }
};

RC_GTEST_PROP(SetProperties, SetStateMachine, ()) {
    SetModel model{};
    IntSet sut;
    rc::state::check(model, sut, &rc::state::gen::execOneOfWithArgs<Insert, Erase>);
}
