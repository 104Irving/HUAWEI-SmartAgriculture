enum TimeTable {
  ZERO, ONE, TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,ELEVEN,TWELVE
}

//弹窗
// @CustomDialog
// struct CustomDialogExample {
//   @State Hour:string = ''
//   controller: CustomDialogController
//   cancel: () => void
//   confirm: () => void
//   build() {
//     Column() {
//       Text('我是内容').fontSize(20).margin({ top: 10, bottom: 10 })
//       Flex({ justifyContent: FlexAlign.SpaceAround }) {
//         Button('cancel')
//           .onClick(() => {
//             this.controller.close()
//             this.cancel()
//           }).backgroundColor(0xffffff).fontColor(Color.Black)
//         Button('confirm')
//           .onClick(() => {
//             this.controller.close()
//             this.confirm()
//           }).backgroundColor(0xffffff).fontColor(Color.Red)
//       }.margin({ bottom: 10 })
//     }
//   }
// }

@Component
export struct WaterPlanComponent {
  @State selectTime: Date = new Date('2020-12-25T08:30:00')
  // dialogController: CustomDialogController = new CustomDialogController({
  //   builder: CustomDialogExample({
  //     cancel: this.onCancel,
  //     confirm: this.onAccept,
  //   }),
  //   alignment: DialogAlignment.Default,  // 可设置dialog的对齐方式，设定显示在底部或中间等，默认为底部显示
  // })
  // onCancel() {
  //   console.log('Callback when the first button is clicked')
  // }
  // onAccept() {
  //   console.log('Callback when the second button is clicked')
  // }

  build() {
    Column({space:8}) {
      // Button("TimePickerDialog 24小时制")
      //   .margin(20)
      //   .onClick(() => {
      //     TimePickerDialog.show({
      //       selected: this.selectTime,
      //       useMilitaryTime: true,
      //       onAccept: (value: TimePickerResult) => {
      //         this.selectTime.setHours(value.hour, value.minute)
      //         console.info("TimePickerDialog:onAccept()" + JSON.stringify(value))
      //       },
      //       onCancel: () => {
      //         console.info("TimePickerDialog:onCancel()")
      //       },
      //       onChange: (value: TimePickerResult) => {
      //         console.info("TimePickerDialog:onChange()" + JSON.stringify(value))
      //       }
      //     })
      //   })

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
          Text('每天')}
        Row(){
          Radio({ value: '2', group: 'frequency' }).checked(false)
          Text('每周')}
        Row(){
          Radio({ value: '3', group: 'frequency' }).checked(false)
          Text('每月')}
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)

      Row(){
        Text('开始时间:')
          .fontSize(22)
          .fontWeight(FontWeight.Bold)
        Row(){Text(`${this.selectTime.getHours()}:${this.selectTime.getMinutes()}`)}
      }
      .width('95%')
      .justifyContent(FlexAlign.SpaceBetween)
      .onClick(() => {
        TimePickerDialog.show({
          selected: this.selectTime,
          useMilitaryTime: true,
          onAccept: (value: TimePickerResult) => {
            this.selectTime.setHours(value.hour, value.minute)
          }
        })
      })

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

@Component
export struct VentilatePlanComponent {
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
