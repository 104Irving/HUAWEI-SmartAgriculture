/*tyh
* * * * * * * * * * * * * * *
* * * * * * * * * * * * * * *
* * * 前端项目主体由式北完成 * * *
* * * * * * * * * * * * * * *
* * * * * * * * * * * * * * *
 */

import { LRComponent } from '../view/RegisterAndLoginComponent';

@Entry
@Component
struct Index {
  @State username: string = ''
  @State password: string = ''

  build() {
    Flex({direction:FlexDirection.Column,alignItems:ItemAlign.Center,justifyContent:FlexAlign.SpaceAround}){

      Text('农业灌溉登入端')
        .fontSize(24)
        .fontColor(0xCC6CE7)
        .fontWeight(FontWeight.Bold)

      LRComponent()
    }
    .backgroundImage($r('app.media.maitianbg'))
    .backgroundImageSize(ImageSize.Cover)


  }

  //页面切换
  pageTransition(){
    PageTransitionEnter({ duration: 600 })
      .opacity(0)
    PageTransitionExit({ duration: 600 })
      .opacity(0)
  }
}