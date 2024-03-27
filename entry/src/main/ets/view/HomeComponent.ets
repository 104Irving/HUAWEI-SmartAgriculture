import FarmBean from '../common/bean/FarmBean';
import UserInfoBean from '../Common/Bean/UserInfoBean';
import router from '@ohos.router';

@Component
export default struct HomeComponent {
  UserInfo: UserInfoBean

  //测试数据
  @State FarmList:FarmBean[] =
    [ new FarmBean(0, '一号田', 22.5, 56, 30, 800, 25),
      new FarmBean(1, '二号田', 22.5, 57, 30, 800, 25),
      new FarmBean(2, '三号田', 22.5, 58, 30, 800, 25),
      new FarmBean(3, '四号田', 22.5, 59, 30, 800, 25),
      new FarmBean(4, 'fufu的大米田', 22.5, 60, 30, 800, 25)]
  @State FarmDetailShow:boolean[] = [false, false, false, false,false]

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
    .onClick(()=>{
      router.pushUrl({
        url:'pages/DetailChart',
        params: name
      })
      console.log(name)
    })
  }

  //显示农田的数据的函数
  @Builder DetailShow(FarmbeanObj: FarmBean) {
    Column(){
      Divider()
        .width('95%')
      Text('传感器数据')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({ top: 10 })
      Divider()
        .width('95%')
      this.ElementShow('温度', FarmbeanObj.temperature)
      this.ElementShow('空气湿度', FarmbeanObj.humidity)
      this.ElementShow('二氧化碳', FarmbeanObj.co2)
      this.ElementShow('光照', FarmbeanObj.lumination)
      this.ElementShow('二氧化碳', FarmbeanObj.co2)
      this.ElementShow('土壤湿度', FarmbeanObj.soilHumidity)
    }
    .transition({type:TransitionType.Insert, opacity:0})
    // .opacity(this.FarmDetailShow[index]?1:0)//透明度选项
    // .animation({duration: 650, curve: Curve.Smooth})
  }

  //农田列表子项呈现的函数
  @Builder FarmListItem(name:string,index:number){
    Column(){
      Row() {
        Row(){
          Image($r('app.media.leaf'))
            .width(40)
            .height(40)
            .margin(10)

          Text(name)
            .fontSize(20)
        }.align(Alignment.TopStart)
      }

      Row(){
        if(this.FarmDetailShow[index]==true){
          this.DetailShow(this.FarmList[index])
        }
      }
      .opacity(this.FarmDetailShow[index]?0.9:0)//透明度选项
    }
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

      //显示农田列表
      List() {
        ForEach(this.FarmDetailShow, (FarmShow:boolean, index:number) => {
          ListItem() {
            this.FarmListItem(this.FarmList[index].name, this.FarmList[index].fieldId)
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
      .listDirection(Axis.Vertical) //列表垂直方向布局
      // .divider({//列表项目的分割线
      //   strokeWidth: 1,
      //   startMargin: 60,
      //   endMargin: 10,
      //   color: '#a1949494' })
      // .scrollBar(BarState.Auto)
      Divider().width('95%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')

  }
}
