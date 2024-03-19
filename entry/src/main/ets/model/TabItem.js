export var TabID;
(function (TabID) {
    TabID[TabID["HOME"] = 0] = "HOME";
    TabID[TabID["WATER_PLAN"] = 1] = "WATER_PLAN";
    TabID[TabID["MINE"] = 2] = "MINE";
})(TabID || (TabID = {}));
export const TabItemList = [
    {
        icon: $r('app.media.home0'),
        icon_selected: $r('app.media.home1'),
        title: '主页',
        id: TabID.HOME
    },
    {
        icon: $r('app.media.water0'),
        icon_selected: $r('app.media.water1'),
        title: '灌溉计划',
        id: TabID.WATER_PLAN
    },
    {
        icon: $r('app.media.user0'),
        icon_selected: $r('app.media.user1'),
        title: '我的',
        id: TabID.MINE
    }
];
//# sourceMappingURL=TabItem.js.map