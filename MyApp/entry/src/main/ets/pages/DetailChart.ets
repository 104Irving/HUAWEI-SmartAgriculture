
import router from '@ohos.router'
import {McLineChart, Options} from '@mcui/mccharts'
import { VentilatePlanComponent, WaterPlanComponent } from '../view/OperationPlanComponent'
import {ChartItem, ChartItemList} from '../model/ChartItem'
import { InDoorTabId, InDoorTabList } from '../model/TabItem'



//显示该农田某一项数据具体信息及时间轴图标的页面
@Entry
@Component
struct DetailChart {
  @State ChartItemShowList: boolean[] = [false, false, false, false, false]
  @State OperationShow:boolean = false //是否显示灌溉计划的控制量
  @State PageIndex: number = 0;//tab转换控制

  //测试用数据图标
  @State seriesOption: Options = new Options({
    xAxis: {
      data: ['周一', '周二', '周三', '周四', '周五', '周六', '周日']
    },
    yAxis: {
      name: '温度'
    },
    series: [
      {
        name: '最高气温',
        data: [11, 11, 15, 13, 12, 13, 10]
      }
    ]
  })

  //数据图标的更新
  aboutToAppear() {
    // setTimeout(() => {
    //   // 传递需要修改的属性与数值，不需要全部传
    //   this.seriesOption.setVal({
    //     series:[
    //       {
    //         name:'最高气温',
    //         data:[110, 110, 150, 130, 120, 190, 100]
    //       },
    //     {
    //     name:'最低气温',
    //     data:[1, -20, 2, 5, 3, 2, 0]
    //   }
    //     ]
    //   })
    // }, 2000)
  }

  //呈现数据图表的函数
  @Builder
  ListItemShow(index: number) {
    Column() {
      Row() {
        Image(ChartItemList[index].Image)
          .objectFit(ImageFit.Contain)
          .width(40)
          .height(40)
          .margin(10)

        Text(`${ChartItemList[index].ItemName}`)
          .fontSize(30)
      }.width("100%")

      if (this.ChartItemShowList[index]) {
        Column() {
          McLineChart({ options: this.seriesOption })
        }
        .width('100%')
        .height('50%')
        .transition({ type: TransitionType.All, opacity: 0, translate: { x: 0, y: -200 } })
      }
    }
  }

  //tab控制转换器
  @Builder MyTabBuilder(idx: number){
    Column(){
      Image(idx == this.PageIndex ? InDoorTabList[idx].icon_selected : InDoorTabList[idx].icon)
        .width(32)
        .height(32)
      Text(InDoorTabList[idx].title)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor(this.PageIndex === idx ? '#006eee':'#888')
    }
  }

  //主体
  build() {
    Column() {
      if(!this.OperationShow){

        //空页面头,占位用
        Column(){}.height("2%").backgroundColor("#fff6e5e5")
        Row({space:8}){

          //天气状况
          Column(){
            Text("天气情况(未完成)")
              .fontSize(30)
          }
          .width("45%")
          .height("30%")
          .backgroundColor("#ffc10d0d")

          //预计降雨
          Column({space:8}){
            Text("预计降雨\n(未完成)")
              .fontSize(30)
            Text("想想再加一个什么模块\n(未完成)")
              .fontSize(30)
          }
          .width("50%")
          .backgroundColor("#ff00e231")
        }
        .transition({ type: TransitionType.All, opacity: 0})

        Button('管理农田')
          .transition({ type: TransitionType.All, opacity: 0})
          .onClick(()=>{
            animateTo({ duration: 200, curve: Curve.Smooth},
              () => {this.OperationShow = !this.OperationShow})
          })
      }

      //管理农田界面
      if(this.OperationShow){
        Column(){

          Tabs({barPosition:BarPosition.Start}){
            //灌溉
            TabContent(){WaterPlanComponent()}
            .tabBar(this.MyTabBuilder(InDoorTabId.WaterPump))

            //通风
            TabContent(){VentilatePlanComponent()}
            .tabBar(this.MyTabBuilder(InDoorTabId.Ventilate))

            //补光
            TabContent(){}
            .tabBar(this.MyTabBuilder(InDoorTabId.LightSub))
          }
          .barWidth('100%')
          .barMode(BarMode.Fixed)
          .width('100%')
          .height('100%')
          .onChange((index)=>{//绑定onChange函数切换页签
            this.PageIndex = index;
          })
        }
          .transition({ type: TransitionType.All, opacity: 0, translate: { x: 0, y: -200 } })
          .width('100%')
          .height('60%')
          .backgroundColor('#f1f2f3')
          .onClick(()=>{
            animateTo({ duration: 300, curve: Curve.Smooth },
              () => {
                this.OperationShow = !this.OperationShow
              })
          })
      }

      //具体数据及显示图标的列表
      List({ space: 8 }) {
        ForEach(ChartItemList, (Item: ChartItem, index: number) => {
          ListItem() {
            this.ListItemShow(index)
          }
          .backgroundColor("#ffffff")
          .onClick(() => {
            animateTo({ duration: 250, curve: Curve.Smooth },
              () => {
                this.ChartItemShowList[index] = !this.ChartItemShowList[index]
              })
          })
        })
      }
      .height("70%")
      .scrollBar(BarState.Auto)//滑动条
    }
    .width('100%')
    .height('100%')
    .backgroundColor("#ffe9e9e9")

  }

  //页面转换
  pageTransition() {
    PageTransitionEnter({ duration: 1200 })
      .opacity(0)
    PageTransitionExit({ duration: 1000 })
      .opacity(0)
  }
}
