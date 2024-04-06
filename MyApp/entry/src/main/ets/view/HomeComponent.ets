import FarmBean from '../common/bean/FarmBean';
import UserInfoBean from '../Common/Bean/UserInfoBean';
import router from '@ohos.router';
import { ChartItemList} from '../model/ChartItem'
import { FarmIOTabList, FarmTabID } from '../model/TabItem';

@Component
export default struct HomeComponent {
  UserInfo: UserInfoBean
  MyFarmList:FarmBean[]//农田的列表,
  @State PageIndex: number = 0;//tab转换控制
  //测试数据
  @State FarmList:FarmBean[] =
    [ new FarmBean(0, '一号田', 22.5, 56, 30, 800, 25),
      new FarmBean(1, '二号田', 22.5, 57, 30, 800, 25),
      new FarmBean(2, '三号田', 22.5, 58, 30, 800, 25),
      new FarmBean(3, '四号田', 22.5, 59, 30, 800, 25),
      new FarmBean(4, 'fufu的大米田', 22.5, 60, 30, 800, 25)]
  @State FarmDetailShow:boolean[] = [false, false, false, false,false]

  //tab构造函数
  @Builder MyTabBuilder(idx: number){
    Column(){
      Image(idx == this.PageIndex ? FarmIOTabList[idx].icon_selected : FarmIOTabList[idx].icon)
        .width(32)
        .height(32)
      Text(FarmIOTabList[idx].title)
        .fontSize(14)
        .fontWeight(FontWeight.Bold)
        .fontColor(this.PageIndex === idx ? '#006eee':'#888')
    }
  }

  //显示农田每一行的数据的函数
  @Builder ElementShow(name: string, detail: number) {
    Row() {
      Text(`${name}`)
        .fontSize(22)
        .fontWeight(FontWeight.Bold)
      Text(`${detail}`)
        .fontSize(20)
    }
    .width('95%')
    .justifyContent(FlexAlign.SpaceBetween)
  }

  //显示农田的数据的函数
  @Builder DetailShow(FarmbeanObj: FarmBean) {
    Column(){
      Divider()
        .width('95%')
      Row(){
        Image($r('app.media.Senser'))
          .width(40)
          .height(40)
          .margin(10)
          .position({ x: "-15%", y:"20%" })
        Text('传感器数据')
          .fontSize(24)
          .fontWeight(FontWeight.Bold)
          .fontColor(Color.Black)
          .margin({ top: 10 })
      }
      .height("7%")


      Divider()
        .width('95%')

      //每一行都是具体数据
      this.ElementShow(ChartItemList[0].ItemName, FarmbeanObj.temperature)
      this.ElementShow(ChartItemList[1].ItemName, FarmbeanObj.humidity)
      this.ElementShow(ChartItemList[2].ItemName, FarmbeanObj.co2)
      this.ElementShow(ChartItemList[3].ItemName, FarmbeanObj.lumination)
      this.ElementShow(ChartItemList[4].ItemName, FarmbeanObj.soilHumidity)

      //跳转到详细信息及历史数据表的按钮
      Button('详细信息')
      .backgroundColor('#ff3b89cb')
        .onClick(()=>{
          router.pushUrl({
            url:'pages/DetailChart',
            params:{
              'FarmID': FarmbeanObj.fieldID //将被点击的农田ID传入
            }
          })
        })
    }
    .backgroundColor('#ffffffff')
    .transition({type:TransitionType.All, opacity:0})
    .width('100%')
    // .opacity(this.FarmDetailShow[index]?1:0)//透明度选项
    // .animation({duration: 650, curve: Curve.Smooth})
  }

  //农田列表子项呈现的函数
  @Builder FarmListItem(name:string,index:number){
    Column(){
      Row() {
        Row(){
          //叶子
          Image($r('app.media.leaf'))
            .width(40)
            .height(40)
            .margin(10)

          Text(name)
            .fontSize(20)

          //箭头,被点击后会旋转九十度
          Image($r('app.media.Arrow'))
            .width(40)
            .height(40)
            .margin(10)
            .position({ x: "80%", y:"1%" })
            .rotate({angle:this.FarmDetailShow[index]?90:0})
        }.align(Alignment.TopStart)
      }
      .width('100%')
      .backgroundColor('#ffffff')

      //点击后显示具体数据
      Row(){
        if(this.FarmDetailShow[index]==true){
          this.DetailShow(this.MyFarmList[index])
        }
      }
      .opacity(this.FarmDetailShow[index]?0.9:0)
    }
  }

  //展示农田列表的函数
  @Builder FarmListShow(){
    List({space: 8}) {
      ForEach(this.FarmDetailShow, (FarmShow:boolean, index:number) => {
        //FarmShow不能删除,删除会不能预览
        ListItem() {
          this.FarmListItem(this.MyFarmList[index].name, this.MyFarmList[index].fieldID)
        }
        // .opacity(0.7)//透明度选项
        .onClick(()=>{
          animateTo({
            duration: 650,
            curve: Curve.Smooth },
            () => {this.FarmDetailShow[index] = !this.FarmDetailShow[index]})
        })
      })
    }
    .height('100%')
    .listDirection(Axis.Vertical) //列表垂直方向布局
  }

  //主构造体
  build() {
    Column({ space: 8 }) {
      Text('我管理的农田')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({ top: 10 })
      Divider().width('95%')

      //室内外tab转换
      Tabs({barPosition:BarPosition.Start}){
        //室内农田
        TabContent(){this.FarmListShow()}
        .tabBar(this.MyTabBuilder(FarmTabID.INDOOR))
        //室外农田
        TabContent(){this.FarmListShow()}
        .tabBar(this.MyTabBuilder(FarmTabID.OUTDOOR))
      }
      .barWidth('100%')
      .barMode(BarMode.Fixed)
      .width('100%')
      .height('100%')
      .onChange((index)=>{//绑定onChange函数切换页签
        this.PageIndex = index;
      })

    }
    .width('100%')
    .height('100%')
    .backgroundColor('#ffe3e3e3')
  }

  //页面转换
  pageTransition(){
    PageTransitionEnter({ duration: 1200 })
      .opacity(0)
    PageTransitionExit({ duration: 1000 })
      .opacity(0)
  }
}
