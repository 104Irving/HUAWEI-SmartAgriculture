import router from '@ohos.router'
import {McLineChart, Options} from '@mcui/mccharts'
import { LightSubPlanComponent, VentilatePlanComponent, WaterPlanComponent } from '../view/OperationPlanComponent'
import {ChartItem, ChartItemList} from '../model/ChartItem'
import { InDoorTabId, InDoorTabList } from '../model/TabItem'
import axios from '@ohos/axios'
import FarmBean from '../Common/Bean/Farmbean'

const params = router.getParams()
const MyFarmID = params['FarmID']

//显示该农田某一项数据具体信息及时间轴图标的页面
@Entry
@Component
struct DetailChart {

  //控制变量
  private timeID: number = 0 //计时器id
  @State ChartItemShowList: boolean[] = [false, false, false, false, false] //控制每一个列表的显示与否
  @State OperationShow: boolean = false //是否显示管理农田的控制量
  @State PageIndex: number = 0;//tab转换控制

  //数据变量
  @State MyFarm: FarmBean = null //当前农田的相关数据
  @State ResData: any = null //接受数据的中转体
  @State MyOption: Options[] = []//储存各个历史数据的列表,每一个成员都应该是option实例

  //测试用数据图标
  // @State seriesOption: Options = new Options({
  //   xAxis: {
  //     data: ['周一', '周二', '周三', '周四', '周五', '周六', '周日']
  //   },
  //   yAxis: {
  //     name: '温度'
  //   },
  //   series: [
  //     {
  //       name: '最高气温',
  //       data: [11, 11, 15, 13, 12, 13, 10]
  //     }
  //   ]
  // })

  loadFarmData(){//加载农田传感器的数据
    axios({//传递到服务器请求用户管理农田的相关数据
      method:"get",
      url:'47.108.250.206:8080/GetFarmSensorData',
      params: {
        FarmID: MyFarmID
      }
    }).then(res=>{
      if(res.data){
        this.MyFarm = new FarmBean(
          res.data[0],
          res.data[1],
          res.data[2],
          res.data[3],
          res.data[4],
          res.data[5],
          res.data[6])
      }else{//数据获取失败
        // 数据获取失败的处理 todo
      }
    })
  }

  loadHistoricalData(){//加载农田每一个监视量的历史数据
    axios({//传递到服务器请求用户管理农田的相关数据
      method:"get",
      url:'47.108.250.206:8080/GetHistoricalData',
      params: {
        FarmID: MyFarmID
      }
    }).then(res=>{
      if(res.data){//获得数据 todo
        for (let index = 0; index < 5; index++) {
          this.ResData = res.data.dataList //每一个成员都是一个数组
          this.MyOption[index] = new Options({
            xAxis: {
              data: this.ResData[0]  //横轴string[]
            },
            yAxis: {
              name: this.ResData[1] //纵轴string
            },
            series: [
              {
                name: this.ResData[2], //图表名称 string
                data: this.ResData[3]  //数据 number[]
              }
            ]
          })
        }
      }else{//数据获取失败
        // 数据获取失败的处理 todo
      }
    })
  }

  aboutToAppear(){
    //获取农田初始数据
    this.loadFarmData();
    //获取历史图表数据,暂时先只获取一次
    this.loadHistoricalData();

    //每一秒更新一次农田数据
    this.timeID = setInterval(()=>{
      this.loadFarmData()
    }, 1000)
  }

  //数据图表的更新
  // aboutToAppear() {
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
  // }

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
          McLineChart({ options: this.MyOption[index] })
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
            TabContent(){LightSubPlanComponent()}
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
