import { TabID, TabItemList } from '../model/TabItem';
import HomeComponent from '../view/HomeComponent';
import { MineComponent } from '../view/MineComponent';
import { WaterPlanComponent } from '../view/WaterPlanComponent';
struct MainPage extends   {
    constructor() { }
    MyTabBuilder(idx) {
        ;
    }
    build() {
            .barWidth('100%')
            .barMode(BarMode.Fixed)
            .width('100%')
            .height('100%')
            .scrollable(true) // 是否可滑动换页
            .onChange((index) => {
            this.PageIndex = index;
        });
    }
}
//# sourceMappingURL=MainPage.js.map