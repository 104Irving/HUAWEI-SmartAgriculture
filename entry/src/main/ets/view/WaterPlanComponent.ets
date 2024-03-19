@Component
export struct WaterPlanComponent {
  build() {
    Column({space:8}) {
      Text('灌溉计划')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')
      //农田信息
      Row(){
        Text('农田编号:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text('1')

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      Row(){
        Text('农田名称:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text('张万斤的麦田')

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Divider()

      Text('手动灌溉')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')
      Row(){
        Text('开启水阀:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Toggle({type:ToggleType.Switch,isOn:false})

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Divider()

      Text('定时灌溉')
        .fontSize(24)
        .fontWeight(FontWeight.Bold)
        .fontColor(Color.Orange)
        .margin({top:10})
      Divider().width('95%')

      Row(){
        Text('频率:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Row(){
          Radio({ value: '1', group: 'frequency' }).checked(true)
          Text('每天')
        }
        Row(){
          Radio({ value: '2', group: 'frequency' }).checked(false)
          Text('每周')
        }
        Row(){
          Radio({ value: '3', group: 'frequency' }).checked(false)
          Text('每月')
        }

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      Row(){
        Text('开始时间:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Row(){
          Text('9:30')
          // Image($r('app.media.right'))
          //   .width(28)
          //   .height(28)
        }


      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      Row(){
        Text('持续时间:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Text('10分钟')

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      Row(){
        Text('水阀控制:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Toggle({type:ToggleType.Switch,isOn:false})

      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)


    }
    .width('100%')
    .height('100%')
    .backgroundColor('#f1f2f3')
  }
}
