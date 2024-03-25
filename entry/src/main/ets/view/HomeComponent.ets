import FarmBean from '../common/bean/FarmBean';
import UserInfoBean from '../Common/Bean/UserInfoBean';
import MainViewModel from '../model/MainViewModel';

@Component
export default struct HomeComponent {
  UserInfo: UserInfoBean
  @State farmBean: FarmBean = new FarmBean(1, '老张的玉米地', 22.5, 56, 30, 800, 25);
  @State Ifdetailshow: boolean = false;
  private timerId: number = 0; //计时器id，每5秒读取一次数据
  @State FarmList:FarmBean[] =
    [ new FarmBean(1, '一号田', 22.5, 56, 30, 800, 25),
      new FarmBean(2, '二号田', 22.5, 57, 30, 800, 25),
      new FarmBean(3, '三号田', 22.5, 58, 30, 800, 25),
      new FarmBean(4, '四号田', 22.5, 59, 30, 800, 25),
      new FarmBean(5, 'fufu的大米田', 22.5, 60, 30, 800, 25)]
  @State FarmDetailShow:boolean[] = [true, false, false, false,false]

  //显示农田每一行的数据
  @Builder ElementShow(name: String, detail: number) {
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

  //显示农田的数据
  @Builder DetialShow(FarmbeanObj:FarmBean) {
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

  @Builder FarmListItem(name:string,index:number){
    Column(){
      Row() {
        Image($r('app.media.leaf'))
          .width(40)
          .height(40)
          .margin(10)

        Text(name)
          .fontSize(20)
      }

      if(this.FarmDetailShow[index]==true){
        this.DetialShow(this.FarmList[index])
      }

    }

  }

  build() {
    Column({ space: 8 }) {
      Text('我管理的农田')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({ top: 10 })
      Divider().width('95%')
      // Row() {
      //   Select([
      //     { value: '一号田', icon: $r('app.media.leaf') },
      //     { value: '二号田', icon: $r('app.media.leaf') },
      //     { value: '三号田', icon: $r('app.media.leaf') },
      //     { value: '四号田', icon: $r('app.media.leaf') },
      //     { value: '五号田', icon: $r('app.media.leaf') }])
      //     .selected(0)
      //     .value('选择农田')
      //     .font({ size: 24, weight: 600 })
      //     .fontColor('#182431')
      //     .selectedOptionFont({ size: 22, weight: 600 })
      //     .optionFont({ size: 18, weight: 500 })
      //     .onSelect((index: number)=>{
      //       this.Ifdetailshow = true;
      //     })
      // }
      // .width('95%')
      // .justifyContent(FlexAlign.SpaceBetween)
      //显示农田的列表
      List() {
        ForEach(this.FarmDetailShow, (FarmShow:boolean, index:number) => {
          ListItem() {
            this.FarmListItem(this.FarmList[index].name, this.FarmList[index].fieldId)
          }
          .onClick(()=>{
            this.FarmDetailShow[this.FarmList[index].fieldId] = !this.FarmDetailShow[this.FarmList[index].fieldId]
          })
        })
      }
      .listDirection(Axis.Vertical)
      .divider({
        strokeWidth: 1,
        startMargin: 60,
        endMargin: 10,
        color: '#a1949494' })
      .scrollBar(BarState.Auto)


      Divider().width('95%')
    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')

  }
}
