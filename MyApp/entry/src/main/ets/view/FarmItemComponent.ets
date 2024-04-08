import FarmBean from '../Common/Bean/Farmbean'
import UserInfoBean from '../Common/Bean/UserInfoBean'
import { ChartItemList } from '../model/ChartItem'
import router from '@ohos.router'

//没用上,但是别删
@Component
export default struct  FarmListItemComponent{
  UserInfo: UserInfoBean //等待上级组件传递
  MyFarm:FarmBean //空的,等待上级组件传递

  //农田列表子项呈现的函数
  @Builder FarmListItem(){
    Column(){
      Row() {
        Row(){
          //叶子
          Image($r('app.media.leaf'))
            .width(40)
            .height(40)
            .margin(10)

          Text(this.MyFarm.name)
            .fontSize(20)

          //箭头,被点击后会旋转九十度
          Image($r('app.media.Arrow'))
            .width(40)
            .height(40)
            .margin(10)
            .position({ x: "80%", y:"1%" })
            .rotate({angle:this.MyFarm.If_show?90:0})
        }.align(Alignment.TopStart)
      }
      .width('100%')
      .backgroundImage($r('app.media.HalftoneGreen'))
      // .backgroundColor('#ffffff')

      //点击后显示具体数据
      Row(){
        if(this.MyFarm.If_show==true){
          this.DetailShow(this.MyFarm)
        }
      }
      .opacity(this.MyFarm.If_show?0.9:0)
    }
  }

  //显示农田的数据的函数
  @Builder DetailShow(FarmbeanObj: FarmBean) {
    Column(){
      Divider()
        .width('95%')
      Row(){
        Image($r("app.media.Sensor"))
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
              'UserID': this.UserInfo.UserID,
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

  build(){
    this.FarmListItem()
  }

}