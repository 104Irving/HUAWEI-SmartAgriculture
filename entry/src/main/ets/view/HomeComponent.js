import MainViewModel from '../model/MainViewModel';
export default struct HomeComponent extends  {
    constructor() { }
    build() {
            .width('100%')
            .height('100%')
            .backgroundColor('#f1f2f3');
    }
    loadFarmData() {
        this.farmBean = MainViewModel.getFarmData(1);
    }
    aboutToAppear() {
        //当页面出现时获取设备数据
        this.loadFarmData();
        //每隔5秒加载一次数据
        this.timerId = setInterval(() => {
            this.loadFarmData();
        }, 5000);
    }
}
struct InfoShow extends  {
    constructor() { }
    build() {
    }
}
//# sourceMappingURL=HomeComponent.js.map